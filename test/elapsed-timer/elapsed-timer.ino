#include "elapsed-timer.h"

ElapsedTimer autosaveTimer(5000);  // Set timer for 5 minutes.

void setup() {
  Serial.begin(115200);  // Debugging
}

// \hu = hunk undo
// \ha = hunk add

void loop() {
  if (autosaveTimer.status() == COMPLETE) {
    // perhaps notify a dispatcher of this timer's status...
    // have it dispatch a task to autosave Travel data...
    Serial.println("Timer complete!");
    Serial.println("Resetting timer...");
    autosaveTimer.reset();
    Serial.println("Timer reset!");
  }
}  

