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
    void Init(int hour, int minute, int second);
    void Display(TimeType timeType);

  private:
    int mHour;
    int mMinute;
    int mSecond;
};
