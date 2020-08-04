#include <iostream>
using namespace std;

template <typename T> constexpr int checkConstexpr(T) { return 0; }

class testA {
public:
  constexpr testA(int x = 0, int y = 0) noexcept : x_(x), y_(y) {}
  constexpr const int &xValue() const noexcept { return x_; }

public:
  int x_;
  int y_;
};

constexpr testA testAFactory(int x, int y) noexcept {
  return testA(x, y);
}

class AAA {
public:
  explicit constexpr AAA(int a) noexcept : a_(a) {}

  constexpr AAA(const AAA & rhs) noexcept: a_(rhs.a_) { }
  AAA &operator=(const AAA &) noexcept(false) {
    throw 1;
    return *this;
  }
  int a_;
};

constexpr AAA bar() noexcept { return AAA(int(0)); }

int main() {
  int a = 1, b = 2;
  constexpr testA aaa = testAFactory(1, 2);
  cout << noexcept(checkConstexpr(1)) << endl;
  cout << noexcept(checkConstexpr(testAFactory(1, 2))) << endl;
  cout << noexcept(checkConstexpr(testAFactory(1, 2).xValue())) << endl;
  cout << noexcept(checkConstexpr(testAFactory(1, 2).x_)) << endl;

  cout << noexcept(checkConstexpr(testAFactory(a, b))) << endl;
  cout << noexcept(checkConstexpr(testAFactory(a, b).xValue())) << endl;
  cout << noexcept(checkConstexpr(testAFactory(a, b).x_)) << endl;

  cout << noexcept(checkConstexpr(bar())) << endl;
}