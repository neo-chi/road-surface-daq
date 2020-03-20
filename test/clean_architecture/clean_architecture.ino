#include "Arduino.h"

void setup()
{
        delay(1000);  // UNIX
        Serial.begin(115200);
}


void loop()
{
        // Check accelerometer interrupt state
        // if latched, collect impact data and write to file

        // Check gps satellite state
        // if disconnected, change impact and controller states
}


