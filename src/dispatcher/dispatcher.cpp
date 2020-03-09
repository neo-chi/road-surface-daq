#include "dispatcher.h"
#include "elapse_timer.h"

Dispatcher::Dispatcher() {
  Serial.println("Constructed a dispatcher");
  // Nothing to do here...
}

void Dispatcher::Update(observable_id_t id, void *state) {
  Serial.println("Dispatcher::Update(id, state) CALLED");
  if (id == TIMER) {
    timer_state_t STATE = *(timer_state_t *)(state);
    if (STATE == IN_PROGRESS) {
      Serial.println("TIMER IN PROGRESS");
    } else if (STATE == COMPLETE) {
      Serial.println("TIMER COMPLETED");
    } else {
      Serial.println("UNHANDLED TIMER STATE");
    }
  }
}