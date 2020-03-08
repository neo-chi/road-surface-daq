#ifndef _ROAD_SURFACE_DAQ_ENVIRONMENT_H
#define _ROAD_SURFACE_DAQ_ENVIRONMENT_H

#include "Arduino.h"

class Environment {
  public:
    Environment(const float _temperature,
                const float _humidity,
                const float _pressure,
                const float _altitude);
    const float temperature;
    const float humidity;
    const float pressure;
    const float altitude;
    String toLogString();
    String toUploadString();
};

#endif
