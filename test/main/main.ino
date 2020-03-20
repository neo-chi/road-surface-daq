// REGION  todo list
// [ ] this that
// [@] and this
// [@] disable interrupts on setup
// [ ] enable interrupts at the end of setup
// [ ] add impact controller
// [ ] add travel controller
// [ ] add accelerometer global
// [ ] add environmental sensor global
// [ ] add gps global
// [@] add storage global
// [ ] add wifi global
// [ ] manage state
// #REGION

#include "accelerometer.h"
#include "environmental_sensor.h"
#include "gps.h"

// REGION device declarations
Accelerometer accelerometer;
EnvironmentalSensor environmental_sensor;
GPS gps;
// #REGION - device delcarations

void setup()
{
        /**
         * It is important that the device is able to setup properly before
         * interrupts may be handled. For this reason, interrupts are disabled
         * before setup begins.
         */
        cli();  // disable interrupts during setup.

        /// setup serial monitoring
        delay(1000);  // UNIX
        Serial.begin(115200);

        /// accelerometer setup
        if (accelerometer.interrupt_is_latched()) {
                accelerometer.unlatch_interrupt();

        /// gps setup
        if (gps.is_connected_to_satellites()) {
                //> set controller logging behaviour
        } else {
                //> set controller logging behaviour
        }

        /**
         * Now that the devices are setup, interrupts may be handled properly
         * within the loop() function. For this reason, interrupts are enabled
         * again.
         */
        sei();  // enable interrupts after setup is complete.
}

void loop()
{
        // REGION state management
        // #REGION

}
