#include "sectionTwoClasses.hpp"

void Time::Init(int hour, int minute, int second) {
  mHour = hour;
  mMinute = minute;
  mSecond = second;
}

void Time::Display(Time::TimeType timeType) {
  using namespace std::chrono;
  auto time = hours(mHour) + minutes(mMinute) + seconds(mSecond);

  switch (timeType) {
  case Time::TimeType::TwentyFourHours:
    std::cout << "24 hours" << std::endl;
    std::cout << std::format("{:%H:%M:%S}", hh_mm_ss(time)) << std::endl;
    break;

  case Time::TimeType::TwelveHours:
    std::cout << "12 hours" << std::endl;
    std::cout << std::format("{:%I:%M:%S %p}", hh_mm_ss(time)) << std::endl;
    break;
  }
}
