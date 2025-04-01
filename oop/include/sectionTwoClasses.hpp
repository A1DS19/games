#pragma once

#include <iostream>
#include "chrono"
#include "format"

class Time{
  public:
    enum TimeType{
      TwentyFourHours,
      TwelveHours
    };
    Time();
    Time(int hour, int minute, int second);
//    Time(int hour = 10, int minute = 20, int second = 30);
    void Init(int hour, int minute, int second);
    void Display(TimeType timeType);
    ~Time();

  private:
    int mHour;
    int mMinute;
    int mSecond;
};
