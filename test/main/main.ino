#include "dispatcher.h"
#include "observable.h"
#include "elapse_timer.h"

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  Dispatcher dispatcher;
  Timer timer{dispatcher, 10000};
  timer.Set(5000);
  timer.setState(COMPLETE);
}

void loop() {

}