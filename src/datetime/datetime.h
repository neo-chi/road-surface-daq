#ifndef _ROAD_SURFACE_DAQ_DATETIME_H
#define _ROAD_SURFACE_DAQ_DATETIME_H

#include "Arduino.h"

#ifndef _ROAD_SURFACE_DAQ_DATE_H
#include "date.h"
#endif

#ifndef _ROAD_SURFACE_DAQ_TIME_H
#include "Time.h"
#endif

enum filename_t {
  DATE,
  TIME
};

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
