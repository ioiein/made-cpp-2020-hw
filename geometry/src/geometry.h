#pragma once
#include <cmath>
#include <iostream>
#include <vector>

const double PI = 3.141592653589793238463;
const double EPS = 1e-5;

struct Point {
  double x, y;
  Point() {
    x = 0;
    y = 0;
  }

  Point(const double& value1, const double& value2) {
    x = value1;
    y = value2;
  }

  bool operator==(const Point& a) {
    return fabs(x - a.x) < EPS && fabs(y - a.y) < EPS;
  }
  bool operator!=(const Point& a) { return !(*this == a); }
};

double EuclidDistance(const Point& point1, const Point& point2) {
  double result = sqrt((point2.x - point1.x) * (point2.x - point1.x) +
                       (point2.y - point1.y) * (point2.y - point1.y));
  return result;
}

class Line {
 public:
  double a, b;  // ax+b

  Line(const Point& p1, const Point& p2) {
    a = (p1.y - p2.y) / (p1.x - p2.x);
    b = (p1.x * p2.y - p2.x * p1.y) / (p1.x - p2.x);
  }

  Line(const double& value1, const double& value2) {
    a = value1;
    b = value2;
  }

  Line(const Point& point, const double& value) {
    a = value;
    b = point.y - a * point.x;
  }

  bool operator==(const Line& line) {
    return fabs(a - line.a) < EPS && fabs(b - line.b) < EPS;
  }

  bool operator!=(const Line& line) { return !(*this == line); }

  ~Line(){};
};

class Shape {
 public:
  virtual double perimeter() = 0;
  virtual double area() = 0;
  virtual bool operator==(const Shape& another) = 0;
  virtual bool operator!=(const Shape& another) = 0;
  virtual void rotate(const Point& center, const double& angle) = 0;
  virtual void reflex(const Point& center) = 0;
  virtual void reflex(const Line& axis) = 0;
  virtual void scale(Point center, double coefficient) = 0;
  virtual ~Shape() = 0;
};
Shape::~Shape(){};

class Polygon : public Shape {
 protected:
  std::vector<Point> points;

 public:
  Polygon(){};

  Polygon(std::vector<Point> pts) { points = pts; }

  double perimeter() override {
    double result = 0;
    for (size_t i = 0; i < points.size(); i++) {
      result += EuclidDistance(points[i], points[(i + 1) % points.size()]);
    }
    return result;
  }

  double area() override {
    double result = 0;
    for (size_t i = 0; i < points.size(); i++) {
      result += (points[(i + 1) % points.size()].x - points[i].x) *
                (points[(i + 1) % points.size()].y + points[i].y) / 2;
    }
    return fabs(result);
  }

  bool operator==(const Shape& another) override {
    const Polygon* a = dynamic_cast<const Polygon*>(&another);
    if (points.size() != a->points.size()) {
      return false;
    } else {
      size_t i;
      for (i = 0; i < points.size(); i++) {
        if (points[0] == a->points[i]) {
          break;
        }
      }
      if (i == points.size()) {
        return false;
      } else {
        for (size_t j = 1; j < points.size(); j++) {
          if (points[j] != a->points[(j + i) % points.size()] &&
              points[j] != a->points[(i - j + points.size()) % points.size()]) {
            return false;
          }
        }
      }
    }
    return true;
  }

  bool operator!=(const Shape& another) override { return !(*this == another); }

  void rotate(const Point& center, const double& angle) override {
    double new_x, new_y;
    for (size_t i = 0; i < points.size(); i++) {
      new_x = center.x + (points[i].x - center.x) * cos(angle) -
              (points[i].y - center.y) * sin(angle);
      new_y = center.y + (points[i].y - center.y) * cos(angle) +
              (points[i].x - center.x) * sin(angle);
      points[i].x = new_x;
      points[i].y = new_y;
    }
  }

  void reflex(const Point& center) override {
    for (size_t i = 0; i < points.size(); i++) {
      points[i].x = 2 * center.x - points[i].x;
      points[i].y = 2 * center.y - points[i].y;
    }
  }

  void reflex(const Line& axis) override {
    for (size_t i = 0; i < points.size(); i++) {
      Line perpendicular(-1.0 / axis.a, points[i].y + points[i].x / axis.a);
      Point cross((axis.b - perpendicular.b) / (perpendicular.a - axis.a),
                  (perpendicular.a * axis.b - axis.a * perpendicular.b) /
                      (perpendicular.a - axis.a));
      points[i].x = 2 * cross.x - points[i].x;
      points[i].y = 2 * cross.y - points[i].y;
    }
  }

  void scale(Point center, double coefficient) override {
    for (size_t i = 0; i < points.size(); i++) {
      points[i].x = center.x + coefficient * (points[i].x - center.x);
      points[i].y = center.y + coefficient * (points[i].y - center.y);
    }
  }

  size_t verticesCount() { return points.size(); }

  std::vector<Point> getVertices() const { return points; }
};

class Ellipse : public Shape {
 protected:
  std::pair<Point, Point> focus;
  double sum_distance;

 public:
  Ellipse() { sum_distance = 0; }

  Ellipse(Point a, Point b, double distance) {
    focus.first = a;
    focus.second = b;
    sum_distance = distance;
  }

  std::pair<Point, Point> focuses() { return focus; }

  double eccentricity() {
    double result = EuclidDistance(focus.first, focus.second) / sum_distance;
    return result;
  }

  Point center() {
    Point c((focus.first.x + focus.second.x) / 2,
            (focus.first.y + focus.second.y) / 2);
    return c;
  }

  double perimeter() override {
    double a = sum_distance / 2;
    double result = 4 * a * std::comp_ellint_2(eccentricity());
    return result;
  }

  double area() override {
    double a = sum_distance / 2;
    double b = a * sqrt(1 - eccentricity() * eccentricity());
    return PI * a * b;
  }

  bool operator==(const Shape& another) override {
    const Ellipse* a = dynamic_cast<const Ellipse*>(&another);
    if ((focus.first != a->focus.first && focus.second != a->focus.second &&
         focus.first != a->focus.second) ||
        fabs(sum_distance - a->sum_distance) > EPS) {
      return false;
    } else {
      return true;
    }
  }

  bool operator!=(const Shape& another) override { return !(*this == another); }

  void rotate(const Point& center, const double& angle) override {
    focus.first.x = center.x + (focus.first.x - center.x) * cos(angle) -
                    (focus.first.y - center.y) * sin(angle);
    focus.first.y = center.y + (focus.first.y - center.y) * cos(angle) +
                    (focus.first.x - center.x) * sin(angle);
    focus.second.x = center.x + (focus.second.x - center.x) * cos(angle) -
                     (focus.second.y - center.y) * sin(angle);
    focus.second.y = center.y + (focus.second.y - center.y) * cos(angle) +
                     (focus.second.x - center.x) * sin(angle);
  }

  void reflex(const Point& center) override {
    focus.first.x = 2 * center.x - focus.first.x;
    focus.first.y = 2 * center.y - focus.first.y;
    focus.second.x = 2 * center.x - focus.second.x;
    focus.second.y = 2 * center.y - focus.second.y;
  }

  void reflex(const Line& axis) override {
    Line perpendicular_first(-1.0 / axis.a,
                             focus.first.y + focus.first.x / axis.a);
    Point cross_first(
        (axis.b - perpendicular_first.b) / (perpendicular_first.a - axis.a),
        (perpendicular_first.a * axis.b - axis.a * perpendicular_first.b) /
            (perpendicular_first.a - axis.a));
    focus.first.x = 2 * cross_first.x - focus.first.x;
    focus.first.y = 2 * cross_first.y - focus.first.y;

    Line perpendicular_second(-1.0 / axis.a,
                              focus.second.y + focus.second.x / axis.a);
    Point cross_second(
        (axis.b - perpendicular_second.b) / (perpendicular_second.a - axis.a),
        (perpendicular_second.a * axis.b - axis.a * perpendicular_second.b) /
            (perpendicular_second.a - axis.a));
    focus.second.x = 2 * cross_second.x - focus.second.x;
    focus.second.y = 2 * cross_second.y - focus.second.y;
  }

  void scale(Point center, double coefficient) override {
    focus.first.x = center.x + coefficient * (focus.first.x - center.x);
    focus.first.y = center.y + coefficient * (focus.first.y - center.y);

    focus.second.x = center.x + coefficient * (focus.second.x - center.x);
    focus.second.y = center.y + coefficient * (focus.second.y - center.y);
    sum_distance *= coefficient;
  }
};

class Circle : public Ellipse {
 public:
  Circle(Point center, double radious) {
    focus.first = focus.second = center;
    sum_distance = 2 * radious;
  }

  double radius() { return sum_distance / 2; }
};

class Rectangle : public Polygon {
 public:
  Rectangle(){};

  Rectangle(Point a, Point b, double rel) {
    if (b.x < a.x) {
      std::swap(a, b);
    }
    if (rel < 1) {
      rel = 1 / rel;
    }
    double dist = EuclidDistance(a, b);
    double length_short = dist / sqrt(1 + rel * rel);
    double length_long = rel * length_short;
    double aa = length_long * length_long / dist;
    double h = length_long * length_short / dist;
    Point buff(a.x + aa * (b.x - a.x) / dist, a.y + aa * (b.y - a.y) / dist);
    Point c(buff.x + h * (b.y - a.y) / dist, buff.y - h * (b.x - a.x) / dist);
    Point d(buff.x - h * (b.y - a.y) / dist, buff.y + h * (b.x - a.x) / dist);
    points.push_back(a);
    points.push_back(c);
    points.push_back(b);
    points.push_back(d);
  }

  Point center() {
    Point centr((points[0].x + points[2].x) / 2, (points[0].x + points[2].x));
    return centr;
  }

  std::pair<Line, Line> diagonals() {
    Line d1(points[0], points[2]);
    Line d2(points[1], points[3]);
    std::pair<Line, Line> diags(d1, d2);
    return diags;
  }
};

class Square : public Rectangle {
 public:
  Square(Point a, Point b) {
    double dist = EuclidDistance(a, b);
    double length_short = dist / sqrt(2);
    double length_long = length_short;
    double aa = length_long * length_long / dist;
    double h = length_long * length_short / dist;
    Point buff(a.x + aa * (b.x - a.x) / dist, a.y + aa * (b.y - a.y) / dist);
    Point c(buff.x + h * (b.y - a.y) / dist, buff.y - h * (b.x - a.x) / dist);
    Point d(buff.x - h * (b.y - a.y) / dist, buff.y + h * (b.x - a.x) / dist);
    points.push_back(a);
    points.push_back(c);
    points.push_back(b);
    points.push_back(d);
  }

  Circle circumscribedCircle() {
    Circle outcircle(center(), EuclidDistance(points[0], points[2]) / 2);
    return outcircle;
  }

  Circle inscribedCircle() {
    Circle incircle(center(), EuclidDistance(points[0], points[1]) / 2);
    return incircle;
  }
};

class Triangle : public Polygon {
 public:
  Triangle(Point a, Point b, Point c) {
    points.push_back(a);
    points.push_back(b);
    points.push_back(c);
  }

  Circle circumscribedCircle() {
    double side_a = EuclidDistance(points[0], points[1]);
    double size_b = EuclidDistance(points[1], points[2]);
    double size_c = EuclidDistance(points[2], points[0]);
    double radious = side_a * size_b * size_c / (4 * area());
    double d = 2 * (points[0].x * (points[1].y - points[2].y) +
                    points[1].x * (points[2].y - points[0].y) +
                    points[2].x * (points[0].y - points[1].y));
    double center_x = 0;
    double center_y = 0;
    for (size_t i = 0; i < 3; ++i) {
      center_x += (points[i].x * points[i].x + points[i].y * points[i].y) *
                  (points[(i + 1) % 3].y - points[(i + 2) % 3].y) / d;
      center_y += (points[i].x * points[i].x + points[i].y * points[i].y) *
                  (points[(i + 2) % 3].x - points[(i + 1) % 3].x) / d;
    }
    Point center(center_x, center_y);
    Circle out_circle(center, radious);
    return out_circle;
  }

  Circle inscribedCircle() {
    double radious = 2 * area() / perimeter();
    double AB = EuclidDistance(points[0], points[1]);
    double BC = EuclidDistance(points[1], points[2]);
    double CA = EuclidDistance(points[2], points[0]);
    double aa = perimeter() / 2 - BC;
    Point buff(points[0].x + aa * (points[2].x - points[0].x) / CA,
               points[0].y + aa * (points[2].y - points[0].y) / CA);
    Line AC(points[0], points[2]);
    double k = -1.0 / AC.a;
    double center_x, center_y;
    if (buff.x <= points[1].x) {
      center_x = buff.x + radious / sqrt(1.0 + k * k);
    } else {
      center_x = buff.x - radious / sqrt(1.0 + k * k);
    }
    if (buff.y <= points[1].y) {
      center_y = buff.y + k * radious / sqrt(1.0 + k * k);
    } else {
      center_y = buff.y - k * radious / sqrt(1.0 + k * k);
    }
    Point center(center_x, center_y);
    Circle in_circle(center, radious);
    return in_circle;
  }

  Point centroid() {
    double centroid_x = (points[0].x + points[1].x + points[2].x) / 3;
    double centroid_y = (points[0].y + points[1].y + points[2].y) / 3;
    Point cd(centroid_x, centroid_y);
    return cd;
  }

  Point orthocenter() {
    Line AB(points[0], points[1]);
    Line BC(points[1], points[2]);
    Line CA(points[2], points[0]);
    Line C_C(points[2], -1.0 / AB.a);
    Line B_B(points[1], -1.0 / CA.a);
    double x = (B_B.b - C_C.b) / (C_C.a - B_B.a);
    double y = C_C.a * x + C_C.b;
    Point center(x, y);
    return center;
  }

  Line EulerLine() {
    Line euline(centroid(), orthocenter());
    return euline;
  }

  Circle ninePointsCircle() {
    Point mid_AB((points[0].x + points[1].x) / 2,
                 (points[0].y + points[1].y) / 2);
    Point mid_BC((points[1].x + points[2].x) / 2,
                 (points[1].y + points[2].y) / 2);
    Point mid_CA((points[2].x + points[0].x) / 2,
                 (points[2].y + points[0].y) / 2);
    Triangle mid_trangle(mid_AB, mid_BC, mid_CA);
    return mid_trangle.circumscribedCircle();
  }
};