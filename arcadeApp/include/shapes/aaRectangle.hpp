#pragma once

#include <vector>

#include "Vec2D.h"
#include "shapes/shape.hpp"

class AARectangle : public Shape {
public:
  AARectangle();
  AARectangle(const Vec2D &topLeft, unsigned int width, unsigned int height);
  AARectangle(const Vec2D &topLeft, const Vec2D &bottomRigth);
  inline void SetTopleftPoint(const Vec2D &topLeft) { mPoints[0] = topLeft; }
  inline void SetBottomRightPoint(const Vec2D &bottomRight) {
    mPoints[1] = bottomRight;
  }
  inline Vec2D GetTopLeftPoint() const { return mPoints[0]; }
  inline Vec2D GetBottomRigthPoint() const { return mPoints[1]; }
  float GetWidht() const;
  float GetHeigth() const;
  void MoveTo(const Vec2D &position);
  virtual Vec2D GetCenterPoint() const override;
  bool Intersects(const AARectangle &otherRectangle) const;
  bool ContainsPoint(const Vec2D &point) const;
  static AARectangle Inset(const AARectangle &rectangle, Vec2D &insets);
  virtual std::vector<Vec2D> GetPoints() const override;
};
