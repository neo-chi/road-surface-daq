#ifndef _ROAD_SURFACE_DAQ_DISPATCHER_H
#define _ROAD_SURFACE_DAQ_DISPATCHER_H

#include "Arduino.h"

enum observable_id_t {
  TIMER,
  WIFI
};

class Dispatcher {
  public:
    Dispatcher();
    void Update(observable_id_t id, void *state);
  private:
    //bool Execute(Task task);
};

#endif
