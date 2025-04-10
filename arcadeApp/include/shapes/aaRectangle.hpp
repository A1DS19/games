#pragma once

#include "Vec2D.h"
#include "shapes/shape.hpp"

class AARectangle : public Shape {
public:
  AARectangle();
  AARectangle(const Vec2D &topLeft, unsigned int width, unsigned int height);
  AARectangle(const Vec2D &topLeft, const Vec2D &bottomRigth);
};
