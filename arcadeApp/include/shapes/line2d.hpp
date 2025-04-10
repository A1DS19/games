#pragma once

#include "Vec2D.h"

class Line2d {
public:
  Line2d();
  Line2d(float x0, float y0, float x1, float y1);
  Line2d(const Vec2D &p0, const Vec2D &p1);

  inline const Vec2D &GetP0() const { return mP0; }
  inline const Vec2D &GetP1() const { return mP1; }
  inline void SetP0(Vec2D &p0) { mP0 = p0; }
  inline void SetP1(Vec2D &p1) { mP1 = p1; }

  bool operator==(const Line2d &line) const;
  float MinDistanceFrom(const Vec2D &point, bool limitToSegment = false) const;
  Vec2D ClosestPoint(const Vec2D &point, bool limitToSegment = false) const;
  Vec2D Midpoint() const;
  float Slope() const;
  float Length() const;

private:
  Vec2D mP0;
  Vec2D mP1;
};
