#ifndef ROAD_SURFACE_DAQ_H_
#define ROAD_SURFACE_DAQ_H_

#include "Arduino.h"

struct Date {
  uint16_t year;
  uint8_t month;
  uint8_t day;
};

struct Time {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

#endif
