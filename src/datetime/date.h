#ifndef _ROAD_SURFACE_DAQ_DATE_H
#define _ROAD_SURFACE_DAQ_DATE_H

#include "Arduino.h"

class Date {
  public:
    Date(uint16_t _year, uint8_t _month, uint8_t _day);
    ~Date() {};
    uint16_t year;
    uint8_t month;
    uint8_t day;
    String toFileNameString();
    String toLogString();
    String toUploadString();
};

#endif
