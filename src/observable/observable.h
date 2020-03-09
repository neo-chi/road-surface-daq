#ifndef _ROAD_SURFACE_DAQ_OBSERVABLE_H
#define _ROAD_SURFACE_DAQ_OBSERVABLE_H

#include "Arduino.h"
#include "dispatcher.h"

class Observable {
  public:
    Observable();
    Observable(Dispatcher _dispatcher, observable_id_t _id);
    bool setState(void *state);
    void Notify();
  protected:
    Dispatcher dispatcher;
    observable_id_t id;
  private:
    void *state;
};


#endif
