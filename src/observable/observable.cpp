#include "observable.h"

Observable::Observable() {
  Serial.println("Constructed an observable");
}

Observable::Observable(Dispatcher _dispatcher, observable_id_t _id)
    : dispatcher(_dispatcher), id(_id) {
  Serial.println("Dispatcher attached to an observable.");
}

// Sets the state of this object.
bool Observable::setState(void *state) {
  Serial.println("Setting observable object state...");
  this->state = state;
  Serial.println("State set!");

  Serial.println("Notifying dispatcher of state update...");
  this->Notify();
}

// Notify alerts the dispatcher of this objects current state.
void Observable::Notify() {
  Serial.println("Calling dispatcher.Update(id, state)");
  Serial.printf("Update: id = %d\n", id);
  Serial.printf("Update: observable_state = %d\n", *(int *)this->state);
  this->dispatcher.Update(this->id, this->state);
}
