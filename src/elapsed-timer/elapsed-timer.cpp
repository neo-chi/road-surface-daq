#include "elapsed-timer.h"

ElapsedTimer::ElapsedTimer(long notify_time) {
  elapsed_time_ = 0;
  setNotifyTime(notify_time);
}

// Update the status of the timer.

// Return the status of the timer, COMPLETE or IMCOMPLETE.
timer_status_t ElapsedTimer::status() {
  updateStatus();
  return status_;
}

void ElapsedTimer::updateStatus() {
  if (getElapsedTime() > getNotifyTime()) {
    status_ = COMPLETE;
  } else {
    status_ = INCOMPLETE;
  }
}

void ElapsedTimer::setNotifyTime(long notify_time) {
  if (notify_time > 0) {
    notify_time_ = notify_time;
  }
}

long ElapsedTimer::getNotifyTime() {
  return notify_time_;
}

// Return the elapsed time in milliseconds.
long ElapsedTimer::getElapsedTime() {
  return millis() - elapsed_time_;
}

// Reset the elasped time to 0
void ElapsedTimer::reset() {
  elapsed_time_ = millis();
}

void ElapsedTimer::notify() {
  if (status_ == COMPLETE) {
    Serial.println("ElapsedTimer COMPLETE");
    Serial.println("ElapsedTimer notifying dispatcher!");
  } else {
    Serial.println("ElapsedTimer INCOMPLETE");
  }
}

