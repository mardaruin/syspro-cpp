#include <iostream>

using namespace std;

template<typename Derived, int MaxInstances>
struct InstanceLimiter {
protected:
  static int instance_counter;

  InstanceLimiter() {
    if (instance_counter >= MaxInstances) {
      throw std::runtime_error("Instance limit exceeded");
    }
    instance_counter++;
    std::cout << "Created " << typeid(Derived).name() << ", total " << instance_counter << std::endl;
  }

  InstanceLimiter(const InstanceLimiter<Derived, MaxInstances>& other) {
    if (instance_counter >= MaxInstances) {
      throw std::runtime_error("Instance limit exceeded");
    }
    instance_counter++;
    std::cout << "Copied " << typeid(Derived).name() << ", total " << instance_counter << std::endl;
  }

public:
  ~InstanceLimiter<Derived, MaxInstances>() {
    instance_counter--;
    std::cout << "Destroyed " << typeid(Derived).name() << ", total " << instance_counter << std::endl;
  }
};

template<typename Derived, int MaxInstances>
int InstanceLimiter<Derived, MaxInstances>::instance_counter = 0;
