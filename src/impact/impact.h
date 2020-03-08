#ifndef _ROAD_SURFACE_DAQ_IMPACT_H
#define _ROAD_SURFACE_DAQ_IMPACT_H

#include "Arduino.h"
#include "datetime.h"
#include "location.h"


class Impact {
  public:
    Impact(Datetime _datetime, Location _location);
    Datetime datetime;
    Location location;
    const bool is_pothole = true;
    String toLogString();
    String toUploadString();
};

#endif

