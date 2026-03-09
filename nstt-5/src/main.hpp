#include <iostream>
#include <utility>
using namespace std;

template<typename T>
class ScopedPointerDeepCopy {
private:
  T* pointer;

public:
  ScopedPointerDeepCopy(T* raw = nullptr):
      pointer(raw ? new T(*raw) : nullptr) {}

  ScopedPointerDeepCopy(const ScopedPointerDeepCopy<T>& other):
      pointer(other.pointer != nullptr ? new T(*other.pointer) : nullptr) {}

  ScopedPointerDeepCopy<T>& operator=(const ScopedPointerDeepCopy<T>& other) {
    if (this != &other) {
      delete pointer;
      pointer = other.pointer != nullptr ? new T(*other.pointer) : nullptr;
    }
    return *this;
  }

  ScopedPointerDeepCopy(ScopedPointerDeepCopy<T>&& other):
      pointer(std::exchange(other.pointer, nullptr)) {}

  ScopedPointerDeepCopy<T>& operator=(ScopedPointerDeepCopy<T>&& other) {
    if (this != &other) {
      delete pointer;
      pointer = std::exchange(other.pointer, nullptr);
    }
    return *this;
  }

  T* operator->() {
    return pointer;
  }

  ~ScopedPointerDeepCopy() {
    if (pointer) {
      delete pointer;
    }
  }
};

template<typename T>
class ScopedPointerTransferring {
private:
  T* pointer;

public:
  ScopedPointerTransferring(T* raw = nullptr):
      pointer(raw ? new T(*raw) : nullptr) {}

  ScopedPointerTransferring(const ScopedPointerTransferring<T>& other) = delete;

  ScopedPointerTransferring<T>& operator=(const ScopedPointerTransferring<T>& other) = delete;

  ScopedPointerTransferring(ScopedPointerTransferring<T>&& other):
      pointer(std::exchange(other.pointer, nullptr)) {}

  ScopedPointerTransferring operator=(ScopedPointerTransferring<T>&& other) {
    if (this != &other) {
      delete pointer;
      pointer = std::exchange(other.pointer, nullptr);
    }
    return *this;
  }

  T* operator->() {
    return pointer;
  }

  ~ScopedPointerTransferring() {
    if (pointer)
      delete pointer;
  }
};
