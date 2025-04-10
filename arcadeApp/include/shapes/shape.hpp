#pragma once

#include <vector>

#include "Vec2D.h"

class Shape {
public:
  virtual ~Shape();
  virtual Vec2D GetCenterPoint() const = 0;
  inline virtual std::vector<Vec2D> GetPoints() { return mPoints; }
  void MoveBy(const Vec2D &deltaOffset);

protected:
  std::vector<Vec2D> mPoints;
};
