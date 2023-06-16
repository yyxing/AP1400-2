#ifndef Q4_H
#define Q4_H
#include <vector>
#include <iostream>
namespace q4 {
struct Vector2D {
  Vector2D() : x(0), y(0) {}
  Vector2D(double x, double y) : x(x), y(y) {}
  double x{};
  double y{};
};

struct Sensor {
  Sensor(Vector2D pos, double accuracy) : pos(pos), accuracy(accuracy) {}
  Sensor(double x, double y, double accuracy) : accuracy(accuracy) {
    pos = Vector2D(x, y);
  }
  Vector2D pos;
  double accuracy;
};
Vector2D kalman_filter(std::vector<q4::Sensor> sensors) {
  double sum = 0;
  std::for_each(sensors.begin(), sensors.end(),
                [&sum](const Sensor &sensor) -> void { sum += sensor.accuracy; });
  std::vector<double> weights;
  std::for_each(sensors.begin(), sensors.end(),
                [&weights, sum](const Sensor &sensor) -> void { weights.push_back(sensor.accuracy / sum); });
  double x = 0, y = 0;
  size_t i = 0;
  std::for_each(sensors.begin(), sensors.end(),
                [sum, weights, sensors, &x, &y, &i](const Sensor &sensor) -> void {
                  x += (weights[i] * sensors[i].pos.x);
                  y += (weights[i] * sensors[i].pos.y);
                  ++i;
                });
  std::cout << x << "\t" << y << std::endl;
  return Vector2D{x, y};
}
}

#endif //Q4_H