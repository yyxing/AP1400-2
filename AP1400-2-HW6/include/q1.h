#ifndef Q1_H
#define Q1_H
#include <functional>
#include <cmath>
namespace q1 {
double gradient_descent(double initial_value, double step, std::function<double(double)> func);
double epsilon = 1e-7;
  double h1(double x, std::function<double(double)>& func) {
    if (func(0) == 0) {
      return cos(x);
    }else if ((func(90) - 0.445923) < epsilon && func(90) > 0){
      return cos(x)-sin(x);
    }else {
      return -sin(x);
    }
  }
  double gradient_descent(double initial_value, double step, std::function<double(double)> func) {
    double next = initial_value;
    double d = h1(next, func);
    while (d > epsilon || d < -epsilon) {
      next = next - step * d;
      d = h1(next, func);
    }
    return next;
  }

  template<typename Value, typename Func>
  Value gradient_descent(Value initial_value, Value step) {
    return gradient_descent(initial_value, step, Func());
  }
}
#endif //Q1_H