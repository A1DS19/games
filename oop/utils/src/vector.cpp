#include "vector.hpp"

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
