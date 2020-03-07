#ifndef ROAD_SURFACE_DAQ_DTO_H_
#define ROAD_SURFACE_DAQ_DTO_H_

#include "Arduino.h"

// Stores a date, year, month, and day.
//
// Date.toString(): return the String YYYYMMDD.
// Date.toUploadString(): return the String YYYY-MM-DD.
class Date {
  public:
    Date(uint16_t _year, uint8_t _month, uint8_t _day);
    ~Date() {};
    uint16_t year;
    uint8_t month;
    uint8_t day;
    String toString();
    String toLogString();
    String toUploadString();
};

class Time {
  public:
    Time(uint8_t hour, uint8_t minute, uint8_t second);
    ~Time() {};
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    String toString();
    String toLogString();
    String toUploadString();
};

class Datetime {
  public:
    Datetime(Date _date, Time _time);
    Date date;
    Time time_;
    String toString();
    String toLogString();
    String toUploadString();
  private:
};

struct Location {
  float latitude;
  float longitude;
  String toString() {
    String return_string = "";
    const int kSizeLocationString = 30;
    char format[kSizeLocationString];
    sprintf(format, "%0.6lf,%0.6lf", latitude, longitude);
    return_string.concat(format);
    return return_string;
  }
};

struct Travel {
   Datetime datetime;
   Location location;
   bool is_pothole;
};

#endif

