#ifndef _ROAD_SURFACE_DAQ_LOCATION_H
#define _ROAD_SURFACE_DAQ_LOCATION_H

#include "Arduino.h"

class Location {
  public:
    Location(const float latitude, const float longitude);
    ~Location() {};
    const float latitude;
    const float longitude;
    String toLogString();
    String toUploadString();
};

#endif
