#include "main.hpp"

#include <cassert>

#include "sectionThreeClasses.hpp"
#include "sectionTwoClasses.hpp"
#include "vector.hpp"

int main() {
  Time time = Time(1, 2, 3);
  time.Init(5, 29, 10);

  time.Display(Time::TwentyFourHours);
  time.Display(Time::TwelveHours);

  Fraction fractionA;
  Fraction fractionB;
  Fraction fractionC(20, 30);
  Fraction fractionD = Fraction(20, 30);

  assert(fractionA == fractionB);
  assert(fractionC == fractionD);

  std::cout << fractionA;

  Vector2d vectorA;
  Vector2d vectorB;
  std::cout << vectorA;

  auto rva = vectorA * vectorB;
  std::cout << "res *: " << rva << std::endl;

  return EXIT_SUCCESS;
}
