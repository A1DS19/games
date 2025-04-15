#pragma once

#include "Vec2D.h"
#include "shapes/shape.hpp"

class Circle : public Shape {
public:
  Circle();
  Circle(const Vec2D &center, float radius);
  inline virtual Vec2D GetCenterPoint() const override { return mPoints[0]; }
  inline float GetRadius() { return mRadius; }
  inline void SetRadius(float radius) { mRadius = radius; }
  inline void MoveTo(const Vec2D &position) { mPoints[0] = position; }
  bool Intersects(const Circle &circle) const;
  bool ContainsPoint(const Vec2D &point) const;

private:
  float mRadius;
};
