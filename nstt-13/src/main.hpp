#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/types.h>

using namespace std;

template<typename Checker>
struct ArgProcessor {
  int& ind;
  bool& found;
  Checker& checker;

  ArgProcessor(int& _ind, bool& _found, Checker& _checker):
      ind(_ind), found(_found), checker(_checker) {}

  template<typename T>
  void operator()(T&& arg) const {
    if (!found && checker(std::forward<T>(arg))) {
      found = true;
    } else if (!found) {
      ++ind;
    }
  }
};

template<typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker checker, Args&&... args) {
  int ind    = 0;
  bool found = false;
  ArgProcessor<Checker> processor(ind, found, checker);


  (processor(std::forward<Args>(args)), ...);
  return found ? ind : -1;
}
