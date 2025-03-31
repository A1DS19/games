#include "main.hpp"

#include "sectionTwoClasses.hpp"

int main() {
  Time time;
  time.Init(5, 29, 10);

  time.Display(Time::TwentyFourHours);
  time.Display(Time::TwelveHours);

  return EXIT_SUCCESS;
}
