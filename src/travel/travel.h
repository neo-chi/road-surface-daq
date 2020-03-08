#ifndef _ROAD_SURFACE_DAQ_TRAVEl_H
#define _ROAD_SURFACE_DAQ_TRAVEl_H

#include "Arduino.h"
#include "datetime.h"
#include "location.h"

class Travel {
  public:
    Travel(Datetime _datetime, Location _location);
    ~Travel() {};
    Datetime datetime;
    Location location;
    bool is_pothole = true;
    String toLogString();
    String toUploadString();
};

#endif
