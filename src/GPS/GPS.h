#ifndef ROAD_SURFACE_DAQ_GPS_H
#define ROAD_SURFACE_DAQ_GPS_H

#include "Arduino.h"
#include "SparkFun_Ublox_Arduino_Library.h"
#include "dto.h"

class GPS : public SFE_UBLOX_GPS {
  public:
   GPS();
   Date getDate();
   Time getTime();
   Datetime getDatetime();
   Location getLocation();
   bool isConnected();
   void waitForConnection();
};

#endif
