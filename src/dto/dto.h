#ifndef ROAD_SURFACE_DAQ_H_
#define ROAD_SURFACE_DAQ_H_

#include "Arduino.h"

struct Date {
  const uint16_t year;
  const uint8_t month;
  const uint8_t day;
};

struct Time {
  const uint8_t hour;
  const uint8_t minute;
  const uint8_t second;
};

struct Datetime {
  const Date date;
  const Time time;
};

struct Location {
  const float latitude;
  const float longitude;
};

struct Impact {
  const Datetime datetime;
  const Location location;
  const bool is_pothole;
};

#endif
