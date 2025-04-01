#include "sectionThreeClasses.hpp"

// Fraction::Fraction() {
//   this->mFracA = 0;
//   this->mFracB = 0;
// }

Fraction::Fraction(int fracA, int fracB) : mFracA(fracA), mFracB(fracB) {}
int Fraction::Add(int fracA, int fracB) const { return fracA + fracB; }
int Fraction::Divide(int fracA, int fracB) const { return fracA / fracB; }
int Fraction::Substract(int fracA, int fracB) const { return fracA - fracB; }
int Fraction::Multiply(int fracA, int fracB) const { return fracA * fracB; }
bool operator==(const Fraction &fracA, const Fraction &fracB) {
  if (fracA.mFracA == fracB.mFracA && fracA.mFracB == fracB.mFracB) {
    return true;
  }
  return false;
}
std::ostream &operator<<(std::ostream &stream, const Fraction &frac) {
  stream << "frac a " << frac.mFracA << "frac b " << frac.mFracB << std::endl;
  return stream;
}
