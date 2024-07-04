#include <cstddef>
#include <cstdint>

class Point;
class Segment;

class Vector {
 public:
  Vector();

  Vector(int64_t coord_x, int64_t coord_y);

  Vector(const Vector& other);

  Vector(const Point& point_a, const Point& point_b);

  int64_t GetX() const;

  int64_t GetY() const;

  Vector& operator=(const Vector& other);

  int64_t operator*(const Vector& other) const;

  int64_t operator^(const Vector& other) const;

  Vector& operator+=(const Vector& other);

  Vector operator+(const Vector& other) const;

  Vector& operator-=(const Vector& other);

  Vector operator-(const Vector& other) const;

  Vector& operator*=(int64_t scalar);

  Vector operator*(int64_t scalar);

  bool operator==(const Vector& other) const;

  bool operator!=(const Vector& other) const;

  Vector operator-() const;

  size_t Len() const;

  friend Vector operator*(int64_t scalar, const Vector& other);

  ~Vector() = default;

 private:
  int64_t coord_x_ = 0;
  int64_t coord_y_ = 0;
};

class IShape {
 public:
  virtual void Move(const Vector&) = 0;

  virtual bool ContainsPoint(const Point&) const = 0;

  virtual bool CrossSegment(const Segment&) const = 0;

  virtual IShape* Clone() const = 0;

  virtual ~IShape() = default;
};

class Point : public IShape {
 public:
  Point();

  Point(int64_t coord_x, int64_t coord_y);

  Point(const Point& other);

  int64_t GetX() const;

  int64_t GetY() const;

  Point& operator=(const Point& other);

  bool operator==(const Point& other) const;

  bool operator!=(const Point& other) const;

  Vector operator-(const Point& other) const;

  void Move(const Vector& vector) override;

  bool ContainsPoint(const Point& other) const override;

  bool CrossSegment(const Segment& segment) const override;

  IShape* Clone() const override;

  ~Point() = default;

 private:
  int64_t coord_x_ = 0;
  int64_t coord_y_ = 0;
};

class Segment : public IShape {
 public:
  Segment();
  Segment(const Point& point_a, const Point& point_b);

  Segment(const Segment& other);

  Point GetA() const;

  Point GetB() const;

  Segment operator=(const Segment& other);

  bool operator==(const Segment& other) const;

  bool operator!=(const Segment& other) const;

  void Move(const Vector& vector) override;

  bool ContainsPoint(const Point& point) const override;

  bool CrossSegment(const Segment& segment) const override;

  IShape* Clone() const override;

  ~Segment() = default;

 private:
  Point point_a_;
  Point point_b_;
};

class Line : public IShape {
 public:
  Line() = default;

  Line(const Point& point_a, const Point& point_b);

  Line(const Line& other);

  int64_t GetA() const;

  int64_t GetB() const;

  int64_t GetC() const;

  Line operator=(const Line& other);

  bool operator==(const Line& other) const;

  bool operator!=(const Line& other) const;

  void Move(const Vector& vector) override;

  bool ContainsPoint(const Point& point) const override;

  bool CrossSegment(const Segment& segment) const override;

  IShape* Clone() const override;

  ~Line() = default;

 private:
  int64_t koeff_a_;
  int64_t koeff_b_;
  int64_t koeff_c_;
};

class Ray : public IShape {
 public:
  Ray();

  Ray(const Point& start, const Point& end);

  Ray(const Ray& other);

  Point GetA() const;

  Vector GetVector() const;

  Ray& operator=(const Ray& other);

  bool operator==(const Ray& other) const;

  bool operator!=(const Ray& other) const;

  void NormalizeVector();

  void Move(const Vector& vector) override;

  bool ContainsPoint(const Point& point) const override;

  bool CrossSegment(const Segment& segment) const override;

  IShape* Clone() const override;

  ~Ray() = default;

 private:
  Point start_;
  Vector direction_;
};

class Circle : public IShape {
 public:
  Circle() = default;

  Circle(const Point& centre, size_t radius);

  Circle(const Circle& other);

  Point GetCentre() const;

  size_t GetRadius() const;

  Circle operator=(const Circle& other);

  bool operator==(const Circle& other) const;

  bool operator!=(const Circle& other) const;

  void Move(const Vector& vector) override;

  bool ContainsPoint(const Point& point) const override;

  bool CrossSegment(const Segment& segment) const override;

  IShape* Clone() const override;

  ~Circle() = default;

 private:
  Point centre_;
  size_t radius_;
};
