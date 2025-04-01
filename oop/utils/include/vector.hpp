#pragma once

#include <ostream>

class Vector2d {
  public:
    Vector2d();
    Vector2d(int x, int y);
    inline void SetX(int x);
    inline void SetY(int y);
    inline float GetX() const;
    inline float GetY() const;
    friend std::ostream &operator<<(std::ostream &stream,const Vector2d& vector2d);
    bool operator==(const Vector2d &other) const;
    bool operator!=(const Vector2d &other) const;
  private:
    float mx, my;
};
