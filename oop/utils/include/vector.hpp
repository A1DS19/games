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
    Vector2d operator-() const;
    Vector2d operator*(float scale) const;
    Vector2d operator/(float scale) const;
    Vector2d &operator*=(float scale);
    Vector2d &operator/=(float scale);
    friend float operator*(Vector2d &vecA, Vector2d &vecB);
    void Rotate(const float angle, Vector2d &aroundpoint);
    Vector2d RotationResult(float angle, const Vector2d &aroundpoint);

  private:
    float mx, my;
};
