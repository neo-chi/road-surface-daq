#ifndef _ROAD_SURFACE_DAQ_DATETIME_H
#define _ROAD_SURFACE_DAQ_DATETIME_H

#include "Arduino.h"
#include "date.h"
#include "Time.h"


class Datetime {
  public:
    Datetime(Date _date, Time _time);
    Date date;
    Time time;
    String toDateFileName();
    String toTimeFileName();
    String toLogString();
    String toUploadString();
  private:
};

#endif
