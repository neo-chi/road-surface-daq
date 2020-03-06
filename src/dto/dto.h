#ifndef ROAD_SURFACE_DAQ_DTO_H_
#define ROAD_SURFACE_DAQ_DTO_H_

#include "Arduino.h"


struct Date {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  String toString() {
    String return_string = "";
    return_string.concat(year);
    return_string.concat(formatPrependZero(month));
    return_string.concat(formatPrependZero(day));
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

struct Datetime {
  Date date;
  Time time;
  String toString() {
    String return_string = "";
    return_string.concat(date.toString());
    return_string.concat(",");
    return_string.concat(time.toString());
    return return_string;
  }
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

