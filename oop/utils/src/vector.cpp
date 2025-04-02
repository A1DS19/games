#include "vector.hpp"

#include <cassert>

#include "utils.hpp"

Vector2d::Vector2d() : Vector2d(6, 9) {}
Vector2d::Vector2d(int x, int y) : mx(x), my(y) {}
inline void Vector2d::SetX(int x) { mx = x; }
inline void Vector2d::SetY(int y) { my = y; }
inline float Vector2d::GetX() const { return mx; }
inline float Vector2d::GetY() const { return my; }
std::ostream &operator<<(std::ostream &stream, const Vector2d &vector2d) {
  stream << vector2d.mx << " " << vector2d.my << std::endl;
  return stream;
}
bool Vector2d::operator==(const Vector2d &other) const {
  return isEqual(this->mx, other.mx) && isEqual(this->my, other.my);
}
bool Vector2d::operator!=(const Vector2d &other) const {
  return !(*this == other);
}
Vector2d Vector2d::operator-() const { return Vector2d(-mx, -my); }
Vector2d Vector2d::operator*(float scale) const {
  return Vector2d(scale * mx, scale * my);
}
Vector2d Vector2d::operator/(float scale) const {
  assert(fabs(scale) > EPSILON);
  return Vector2d(scale / mx, scale / my);
}
Vector2d &Vector2d::operator*=(float scale) { return *this *= scale; }
Vector2d &Vector2d::operator/=(float scale) {
  assert(fabs(scale) > EPSILON);
  return *this /= scale;
}
float operator*(Vector2d &vecA, Vector2d &vecB) {
  return (vecA.mx * vecB.mx) + (vecA.my + vecB.my);
}
