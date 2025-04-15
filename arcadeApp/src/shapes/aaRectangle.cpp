#include "shapes/aaRectangle.hpp"

#include <vector>

AARectangle::AARectangle() : AARectangle(Vec2D::Zero, Vec2D::Zero) {}

AARectangle::AARectangle(const Vec2D &topLeft, unsigned int width,
                         unsigned int height) {
  mPoints.push_back(topLeft);
  mPoints.push_back(
      Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1));
}

AARectangle::AARectangle(const Vec2D &topLeft, const Vec2D &bottomRigth) {
  mPoints.push_back(topLeft);
  mPoints.push_back(bottomRigth);
}

float AARectangle::GetWidht() const {
  return GetBottomRigthPoint().GetX() - GetTopLeftPoint().GetY() + 1;
}

float AARectangle::GetHeigth() const {
  return GetBottomRigthPoint().GetY() - GetTopLeftPoint().GetX() + 1;
}

void AARectangle::MoveTo(const Vec2D &position) {
  float width = GetWidht();
  float heigth = GetHeigth();

  SetTopleftPoint(position);
  SetBottomRightPoint(
      Vec2D(position.GetX() + width - 1, position.GetY() + heigth - 1));
}

Vec2D AARectangle::GetCenterPoint() const {
  return Vec2D(GetTopLeftPoint().GetX() + GetWidht() / 2.0f,
               GetTopLeftPoint().GetY() + GetHeigth() / 2.0f);
}

bool AARectangle::Intersects(const AARectangle &otherRectangle) const {
  return !(
      otherRectangle.GetBottomRigthPoint().GetX() < GetTopLeftPoint().GetX() ||
      otherRectangle.GetTopLeftPoint().GetX() > GetBottomRigthPoint().GetX() ||
      otherRectangle.GetBottomRigthPoint().GetY() < GetTopLeftPoint().GetY() ||
      otherRectangle.GetTopLeftPoint().GetY() > GetBottomRigthPoint().GetY());
}

bool AARectangle::ContainsPoint(const Vec2D &point) const {
  bool withinX = point.GetX() >= GetTopLeftPoint().GetX() &&
                 point.GetX() <= GetBottomRigthPoint().GetX();

  bool withinY = point.GetY() >= GetTopLeftPoint().GetY() &&
                 point.GetY() <= GetBottomRigthPoint().GetY();

  return withinX && withinY;
}

AARectangle AARectangle::Inset(const AARectangle &rectangle, Vec2D &insets) {
  return AARectangle(rectangle.GetTopLeftPoint() + insets,
                     rectangle.GetWidht() - 2 * insets.GetX(),
                     rectangle.GetHeigth() - 2 * insets.GetY());
}

std::vector<Vec2D> AARectangle::GetPoints() const {
  std::vector<Vec2D> points;
  points.push_back(mPoints[0]);
  points.push_back(Vec2D(mPoints[1].GetX(), mPoints[0].GetY()));
  points.push_back(mPoints[1]);
  points.push_back(Vec2D(mPoints[0].GetX(), mPoints[1].GetY()));

  return points;
}
