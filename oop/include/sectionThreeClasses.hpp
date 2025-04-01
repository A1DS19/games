#pragma once

#include <ostream>
class Fraction{
  public:
    static constexpr int id = 50;

    // Fraction();
    Fraction(int fracA = 0, int fracB = 1); // handles both cases for constuctors
    int Add(const int fracA, const int fracB) const;
    int Substract(const int fracA, const int fracB) const;
    int Divide(const int fracA, const int fracB) const;
    int Multiply(const int fracA, const int fracB) const;
    friend bool operator==(const Fraction &fracA, const Fraction &fracB);
    friend std::ostream &operator<<(std::ostream &stream, const Fraction &frac);

  private:
    int mFracA;
    int mFracB;
};
