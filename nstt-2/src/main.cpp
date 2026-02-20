#include <iostream>
#include <limits>
#include <tuple>

class Point {
public:
  double x;
  double y;

  Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};

// ax + by + c = 0
class Line {
private:
  double a, b, c;

public:
  Line(const Point &p1, const Point &p2) {
    if (p1.y != p2.y) {
      this->a = 1.0;
      this->b = (p1.x - p2.x) / (p2.y - p1.y);
      this->c = (p1.y * p2.x - p2.y * p1.x) / (p2.y - p1.y);
    } else {
      this->a = 0.0;
      this->b = 1.0;
      this->c = -p1.y;
    }
  }

  Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

  double getA() const { return a; }
  double getB() const { return b; }
  double getC() const { return c; }

  std::pair<Point, bool> intersect(const Line &l) const {
    double ind = a * l.b - b * l.a;

    if (std::abs(ind) > 0) { // intersect
      double y = (c * l.a - l.c * a) / ind;
      double x = (0 - b * y + c) / a;
      return {{x, y}, true};
    } else { // parallel or identical
      return {{0, 0}, false};
    }
  }

  Line perpendicular(const Point &p, const Line &l) {
    if (std::abs(l.b) == 0) {
      return Line(0.0, -1.0, p.y);
    } else if (std::abs(l.a) == 0) {
      return Line(-1.0, 0.0, p.x);
    } else {
      return Line(-l.b, l.a, l.b * p.x - l.a * p.y);
    }
  }
};