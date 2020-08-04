#include <iostream>

template <typename T> constexpr int foo(T) { return 0; }

class AAA {
public:
  explicit constexpr AAA(int a) noexcept : a_(a) {}

  explicit AAA(const AAA &) noexcept(false) { throw 1; }
  AAA &operator=(const AAA &) noexcept(false) {
    throw 1;
    return *this;
  }
  int a_;
};

constexpr AAA bar() noexcept { return AAA(0); }

int main() {
  const int a = 5;
  int b = 5;
  constexpr int c = 2;
#define d 10
  std::cout << noexcept(foo(1)) << std::endl;
  std::cout << noexcept(foo(a)) << std::endl;
  std::cout << noexcept(foo(b)) << std::endl;
  std::cout << noexcept(foo(c)) << std::endl;
  std::cout << noexcept(foo(d)) << std::endl;
  std::cout << noexcept(sizeof(int)) << std::endl;
  std::cout << noexcept(foo(bar())) << std::endl;
  std::cout << noexcept(foo(bar().a_)) << std::endl;
  return 0;
}