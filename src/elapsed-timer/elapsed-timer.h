#ifndef _ROAD_SURFACE_DAQ_AUTOSAVETIMER_H
#define _ROAD_SURFACE_DAQ_AUTOSAVETIMER_H

#include "Arduino.h"

enum timer_status_t {
  COMPLETE,
  INCOMPLETE
};

// The ElapsedTimer class is responsible for maintaining the elapsed time
// until a given process must be executed.
// Upon the completion and acknowledgement of the ElapsedTimer, the timer
// will be reset to the current time and the process will be repeated.
class ElapsedTimer {
  public:
   ElapsedTimer(long notify_time);
   void updateStatus();
   timer_status_t status();
   void setNotifyTime(long notify_time);
   long getNotifyTime();
   long getElapsedTime();
   void reset();
   void notify();
  private:
   timer_status_t status_;
   long elapsed_time_;
   long notify_time_;
};

#endif
