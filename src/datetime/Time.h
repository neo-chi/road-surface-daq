#ifndef _ROAD_SURFACE_DAQ_TIME_H
#define _ROAD_SURFACE_DAQ_TIME_H

#include "Arduino.h"

class Time {
  public:
    Time(uint8_t hour, uint8_t minute, uint8_t second);
    ~Time() {};
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    String toFileNameString();
    String toLogString();
    String toUploadString();
};


#endif
