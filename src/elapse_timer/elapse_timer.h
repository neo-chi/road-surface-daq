#ifndef _ROAD_SURFACE_DAQ_TIMER_H
#define _ROAD_SURFACE_DAQ_TIMER_H

#include "Arduino.h"
#include "observable.h"

enum timer_state_t {
  COMPLETE,
  IN_PROGRESS
};

class Timer : public Observable {
  public:
    Timer(Dispatcher _dispatcher, long _time);
    void Update();
    void Set(long _time);
    void Reset();
    void setState(timer_state_t state); // overload
  protected:
    long elapsed_time;
    long set_time;
    timer_state_t state;
    observable_id_t id = TIMER;  // Inherited
};

#endif
