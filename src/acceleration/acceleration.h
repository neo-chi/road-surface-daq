#ifndef _ROAD_SURFACE_DAQ_ACCELERATION_H
#define _ROAD_SURFACE_DAQ_ACCELERATION_H

#include "Arduino.h"

#define NOT_RECORDED -100

class Acceleration {
  public:
    Acceleration(float _x, float _y, float _z);
    float x = NOT_RECORDED;
    float y = NOT_RECORDED;
    float z = NOT_RECORDED;
    String toString();
  private:
    bool _axis_not_recorded(float axis);
};

#endif

