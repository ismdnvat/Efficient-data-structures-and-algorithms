#include "geometry.hpp"

#include <algorithm>

Vector::Vector() : coord_x_(0), coord_y_(0) {}

Vector::Vector(int64_t coord_x, int64_t coord_y)
    : coord_x_(coord_x), coord_y_(coord_y) {}

Vector::Vector(const Vector& other)
    : coord_x_(other.GetX()), coord_y_(other.GetY()) {}

Vector::Vector(const Point& point_a, const Point& point_b)
    : coord_x_(point_b.GetX() - point_a.GetX()),
      coord_y_(point_b.GetY() - point_a.GetY()) {}

int64_t Vector::GetX() const { return coord_x_; }

int64_t Vector::GetY() const { return coord_y_; }

Vector& Vector::operator=(const Vector& other) {
  coord_x_ = other.GetX();
  coord_y_ = other.GetY();
  return *this;
}

int64_t Vector::operator*(const Vector& other) const {
  return coord_x_ * other.coord_x_ + coord_y_ * other.coord_y_;
}

int64_t Vector::operator^(const Vector& other) const {
  return coord_x_ * other.coord_y_ - coord_y_ * other.coord_x_;
}

Vector& Vector::operator+=(const Vector& other) {
  coord_x_ += other.coord_x_;
  coord_y_ += other.coord_y_;
  return *this;
}

Vector Vector::operator+(const Vector& other) const {
  return Vector(*this) += other;
}

Vector& Vector::operator-=(const Vector& other) {
  coord_x_ -= other.coord_x_;
  coord_y_ -= other.coord_y_;
  return *this;
}

Vector Vector::operator-(const Vector& other) const {
  return Vector(*this) -= other;
}

Vector& Vector::operator*=(int64_t scalar) {
  coord_x_ *= scalar;
  coord_y_ *= scalar;
  return *this;
}

Vector Vector::operator*(int64_t scalar) { return {*this *= scalar}; }

bool Vector::operator==(const Vector& other) const {
  return (coord_x_ == other.GetX()) && (coord_y_ == other.GetY());
}

bool Vector::operator!=(const Vector& other) const { return !(*this == other); }

Vector Vector::operator-() const { return Vector(*this) *= -1; }

Vector operator*(int64_t scalar, const Vector& other) {
  return Vector(other) *= scalar;
}

size_t Vector::Len() const {
  return (size_t)(coord_x_ * coord_x_) + coord_y_ * coord_y_;
}

Point::Point() : coord_x_(0), coord_y_(0) {}

Point::Point(int64_t coord_x, int64_t coord_y)
    : coord_x_(coord_x), coord_y_(coord_y) {}

Point::Point(const Point& other)
    : coord_x_(other.GetX()), coord_y_(other.GetY()) {}

int64_t Point::GetX() const { return coord_x_; }

int64_t Point::GetY() const { return coord_y_; }

Point& Point::operator=(const Point& other) {
  coord_x_ = other.GetX();
  coord_y_ = other.GetY();
  return *this;
}

bool Point::operator==(const Point& other) const {
  return (coord_x_ == other.GetX()) && (coord_y_ == other.GetY());
}

bool Point::operator!=(const Point& other) const { return !(*this == other); }

Vector Point::operator-(const Point& other) const {
  return Vector(other, *this);
}

void Point::Move(const Vector& vector) {
  coord_x_ += vector.GetX();
  coord_y_ += vector.GetY();
}

bool Point::ContainsPoint(const Point& other) const { return *this == other; }

bool Point::CrossSegment(const Segment& segment) const {
  Vector vector_point_to_a(*this, segment.GetA());
  Vector vector_point_to_b(*this, segment.GetB());
  return (vector_point_to_a ^ vector_point_to_b) == 0 &&
         (vector_point_to_b * vector_point_to_a) <= 0;
}

IShape* Point::Clone() const { return new Point(*this); }

Segment::Segment() { point_a_ = point_b_ = Point(); }

Segment::Segment(const Point& point_a, const Point& point_b)
    : point_a_(point_a), point_b_(point_b) {}

Segment::Segment(const Segment& other) {
  point_a_ = other.point_a_;
  point_b_ = other.point_b_;
}

Point Segment::GetA() const { return point_a_; }

Point Segment::GetB() const { return point_b_; }

Segment Segment::operator=(const Segment& other) {
  point_a_ = other.GetA();
  point_b_ = other.GetB();
  return *this;
}

bool Segment::operator==(const Segment& other) const {
  return (point_a_ == other.GetA()) && (point_b_ == other.GetB());
}

bool Segment::operator!=(const Segment& other) const {
  return !(*this == other);
}

void Segment::Move(const Vector& vector) {
  point_a_.Move(vector);
  point_b_.Move(vector);
}

bool Segment::ContainsPoint(const Point& point) const {
  return point.CrossSegment(*this);
}

bool FindIntersection(int64_t x_1, int64_t y_1, int64_t x_2, int64_t y_2) {
  if (x_1 > y_1) {
    std::swap(x_1, y_1);
  }
  if (x_2 > y_2) {
    std::swap(x_2, y_2);
  }
  return (y_1 >= x_2) && (y_2 >= x_1);
}

bool Segment::CrossSegment(const Segment& segment) const {
  bool intersection_x =
      FindIntersection(point_a_.GetX(), point_b_.GetX(),
                       segment.point_a_.GetX(), segment.point_b_.GetX());
  bool intersection_y =
      FindIntersection(point_a_.GetY(), point_b_.GetY(),
                       segment.point_a_.GetY(), segment.point_b_.GetY());
  if (intersection_x && intersection_y) {
    Vector vec_of_this(point_a_, point_b_);
    Vector vec_of_segment(segment.point_a_, segment.point_b_);
    bool orientation1 =
        ((vec_of_this ^ Vector(point_a_, segment.point_a_)) *
         (vec_of_this ^ Vector(point_a_, segment.point_b_))) <= 0;
    bool orientation2 =
        ((vec_of_segment ^ Vector(segment.point_a_, point_a_)) *
         (vec_of_segment ^ Vector(segment.point_a_, point_b_))) <= 0;

    return orientation1 && orientation2;
  }
  return false;
}

IShape* Segment::Clone() const { return new Segment(*this); }

Line::Line(const Point& point_a, const Point& point_b) {
  koeff_a_ = point_b.GetY() - point_a.GetY();
  koeff_b_ = point_a.GetX() - point_b.GetX();
  koeff_c_ = point_b.GetX() * point_a.GetY() - point_a.GetX() * point_b.GetY();
}

Line::Line(const Line& other)
    : koeff_a_(other.GetA()), koeff_b_(other.GetB()), koeff_c_(other.GetC()) {}

int64_t Line::GetA() const { return koeff_a_; }

int64_t Line::GetB() const { return koeff_b_; }

int64_t Line::GetC() const { return koeff_c_; }

Line Line::operator=(const Line& other) {
  koeff_a_ = other.GetA();
  koeff_b_ = other.GetB();
  koeff_c_ = other.GetC();
  return *this;
}

bool Line::operator==(const Line& other) const {
  return ((koeff_a_ == other.GetA()) && (koeff_b_ == other.GetB()) &&
          (koeff_c_ == other.GetC()));
}

bool Line::operator!=(const Line& other) const { return !(*this == other); }

void Line::Move(const Vector& vector) {
  koeff_c_ -= (koeff_a_ * vector.GetX() + koeff_b_ * vector.GetY());
}

bool Line::ContainsPoint(const Point& point) const {
  return koeff_a_ * point.GetX() + koeff_b_ * point.GetY() + koeff_c_ == 0;
}

bool Line::CrossSegment(const Segment& segment) const {
  int64_t value1 = koeff_a_ * segment.GetA().GetX() +
                   koeff_b_ * segment.GetA().GetY() + koeff_c_;
  int64_t value2 = koeff_a_ * segment.GetB().GetX() +
                   koeff_b_ * segment.GetB().GetY() + koeff_c_;
  return value1 * value2 <= 0;
}

IShape* Line::Clone() const { return new Line(*this); }

void Ray::NormalizeVector() {
  int64_t com_divisor = std::__gcd((int64_t)std::abs(direction_.GetX()),
                                   (int64_t)std::abs(direction_.GetY()));
  com_divisor = (com_divisor == 0) ? 1 : com_divisor;
  direction_ =
      Vector(direction_.GetX() / com_divisor, direction_.GetY() / com_divisor);
}

Ray::Ray() {
  start_ = Point();
  direction_ = Vector();
}

Ray::Ray(const Point& start, const Point& end)
    : start_(start), direction_(end - start) {
  NormalizeVector();
}

Ray::Ray(const Ray& other)
    : start_(other.GetA()), direction_(other.GetVector()) {}

Point Ray::GetA() const { return start_; }

Vector Ray::GetVector() const { return direction_; }

Ray& Ray::operator=(const Ray& other) {
  start_ = other.GetA();
  direction_ = other.GetVector();
  return *this;
}

bool Ray::operator==(const Ray& other) const {
  return (start_ == other.GetA()) && (direction_ == other.GetVector());
}

bool Ray::operator!=(const Ray& other) const { return !(*this == other); }

void Ray::Move(const Vector& vector) { start_.Move(vector); }

bool Ray::ContainsPoint(const Point& point) const {
  Ray new_ray(start_, point);
  if (new_ray.GetVector() != Vector()) {
    return new_ray == *this;
  }
  return true;
}

bool Ray::CrossSegment(const Segment& segment) const {
  if (segment.ContainsPoint(start_)) {
    return true;
  }
  Point end_point(start_.GetX() + direction_.GetX(),
                  start_.GetY() + direction_.GetY());
  if (!(Line(start_, end_point)).CrossSegment(segment)) {
    return false;
  }

  int64_t cross_product_segment1 =
      ((start_ - segment.GetA()) ^ (segment.GetB() - segment.GetA()));
  int64_t cross_product_segment2 =
      (direction_ ^ (segment.GetB() - segment.GetA()));
  if (cross_product_segment1 == 0 && cross_product_segment2 == 0) {
    return ContainsPoint(segment.GetA()) || ContainsPoint(segment.GetB());
  }
  return cross_product_segment1 * cross_product_segment2 < 0;
}

IShape* Ray::Clone() const { return new Ray(*this); }

Circle::Circle(const Point& centre, size_t radius)
    : centre_(centre), radius_(radius) {}

Circle::Circle(const Circle& other)
    : centre_(other.GetCentre()), radius_(other.GetRadius()) {}

Point Circle::GetCentre() const { return centre_; }

size_t Circle::GetRadius() const { return radius_; }

Circle Circle::operator=(const Circle& other) {
  centre_ = other.GetCentre();
  radius_ = other.GetRadius();
  return *this;
}

bool Circle::operator==(const Circle& other) const {
  return ((centre_ == other.GetCentre()) && (radius_ == other.GetRadius()));
}

bool Circle::operator!=(const Circle& other) const { return !(*this == other); }

void Circle::Move(const Vector& vector) { centre_.Move(vector); }

bool Circle::ContainsPoint(const Point& point) const {
  int64_t distance_squared =
      (point.GetX() - centre_.GetX()) * (point.GetX() - centre_.GetX()) +
      (point.GetY() - centre_.GetY()) * (point.GetY() - centre_.GetY());
  return distance_squared <= static_cast<int64_t>(radius_ * radius_);
}

bool Circle::CrossSegment(const Segment& segment) const {
  size_t dist;
  Vector segment_direction = segment.GetB() - segment.GetA();
  Vector to_point_a = centre_ - segment.GetA();
  Vector to_point_b = centre_ - segment.GetB();

  if (segment_direction * to_point_a <= 0) {
    dist = to_point_a.Len();
  } else if ((-segment_direction) * to_point_b <= 0) {
    dist = to_point_b.Len();
  } else {
    dist = static_cast<size_t>(
        ((segment_direction ^ to_point_a) * (segment_direction ^ to_point_a)) /
        segment_direction.Len());
  }
  size_t dist1 = Vector(centre_ - segment.GetA()).Len();
  size_t dist2 = Vector(centre_ - segment.GetB()).Len();
  if (dist1 > dist2) {
    std::swap(dist1, dist2);
  }
  bool is_inside_circle = dist <= radius_ * radius_;
  bool both_outside = dist1 < radius_ * radius_ && dist2 < radius_ * radius_;

  return is_inside_circle && !both_outside;
}

IShape* Circle::Clone() const { return new Circle(*this); }
