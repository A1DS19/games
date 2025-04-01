#include "sectionTwoClasses.hpp"

void Time::Init(int hour, int minute, int second) {
  mHour = hour;
  mMinute = minute;
  mSecond = second;
}

Time::Time() {
  mHour = 0;
  mMinute = 0;
  mSecond = 0;
}

Time::Time(int hour, int minute, int second) {
  mHour = hour;
  mMinute = minute;
  mSecond = second;
}

Time::~Time() {
  mMinute = 0;
  mSecond = 0;
  mHour = 0;

  std::cout << "detroyed all data" << std::endl;
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
