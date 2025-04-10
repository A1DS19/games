#include "shapes/line2d.hpp"

#include <cmath>

#include "Utils.h"
#include "Vec2D.h"

Line2d::Line2d() : Line2d(Vec2D::Zero, Vec2D::Zero) {}

Line2d::Line2d(float x0, float y0, float x1, float y1)
    : Line2d(Vec2D(x0, y0), Vec2D(x1, y1)) {}

Line2d::Line2d(const Vec2D &p0, const Vec2D &p1) : mP0(p0), mP1(p1) {}

bool Line2d::operator==(const Line2d &line) const {
  return line.GetP0() == mP0 && line.GetP1() == mP1;
}

float Line2d::Slope() const {
  float dx = mP1.GetX() - mP0.GetX();

  if (fabsf(dx) < EPSILON) {
    return 0;
  }

  float dy = mP1.GetY() - mP0.GetY();

  return dy / dx;
}

Vec2D Line2d::Midpoint() const {
  return Vec2D((mP0.GetX() + mP1.GetX()) / 2.0f,
               (mP0.GetY() + mP1.GetY()) / 2.0f);
}

float Line2d::MinDistanceFrom(const Vec2D &p, bool limitToSegment) const {
  return p.Distance(ClosestPoint(p, limitToSegment));
}

Vec2D Line2d::ClosestPoint(const Vec2D &p, bool limitToSegment) const {
  Vec2D p0ToP = p - mP0;

  Vec2D p0ToP1 = mP1 - mP0;

  float l2 = p0ToP1.Mag2();

  float dot = p0ToP.Dot(p0ToP1);

  float t = dot / l2;

  if (limitToSegment) {
    t = std::fmax(0, std::fmin(1.0f, t));
  }

  return mP0 + p0ToP1 * t;
}

float Line2d::Length() const { return mP1.Distance(mP0); }
