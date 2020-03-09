#include "elapse_timer.h"

Timer::Timer(Dispatcher _dispatcher, long _set_time)
    : Observable{_dispatcher, id}, set_time(_set_time) {
  // Nothing to do here.
}

void Timer::setState(timer_state_t state) {
  this->state = state;
  Observable* observable = this;
  observable->setState(&this->state);
}

void Timer::Set(long _duration) {
  this->set_time = _duration;
  this->state = IN_PROGRESS;
  int _state = (int)state;
  Serial.printf("Timer State to Int: %d\n", _state);
  Observable* observable = this;
  void *__state = &state;
  observable->setState(__state);
}

