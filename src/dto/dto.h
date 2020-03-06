#ifndef ROAD_SURFACE_DAQ_DTO_H_
#define ROAD_SURFACE_DAQ_DTO_H_

#include "Arduino.h"

// Stores a date, year, month, and day.
//
// Date.toString(): return the String YYYYMMDD.
// Date.toUploadString(): return the String YYYY-MM-DD.
class Date {
  public:
    Date();
    Date(uint16_t _year, uint8_t _month, uint8_t _day);
    ~Date() {};
    uint16_t year;
    uint8_t month;
    uint8_t day;
    String toString();
    String toLogString();
    String toUploadString();
};

struct Time {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  String toString() {
    String return_string = "";
    return_string.concat(formatPrependZero(hour));
    return_string.concat(formatPrependZero(minute));
    return_string.concat(formatPrependZero(second));
    return return_string;
  }
  String formatPrependZero(int value) {
    String formatted_string = "";
    if (value > 10) {
      formatted_string.concat(value);
    } else {
      formatted_string.concat(0);
      formatted_string.concat(value);
    }
    return formatted_string;
  }
};

class Datetime {
  public:
    Datetime(Date _date, Time _time);
    Date date;
    Time time;
    String toString(); 
    String toLogString();
    String toUploadString();
    Date getDate();
    Time getTime();
    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();
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

