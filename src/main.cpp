#include <Arduino.h>

#include "accelerometer.h"
#include "environmental_sensor.h"
#include "gps.h"
#include "impact_controller.h"
#include "storage.h"

Accelerometer *accelerometer = new Accelerometer;
EnvironmentalSensor *environmental_sensor = new EnvironmentalSensor;
GPS *gps = new GPS;  // working
Storage *storage = new Storage;
ImpactController impact_controller;

void setup()
{
        delay(1000);  // UNIX
        Serial.begin(9600);

        accelerometer->begin();
        gps->begin();
        storage->begin();

        gps->connect_to_satellites();

        //accelerometer->read(PRE_IMPACT);
        //accelerometer->read(POST_IMPACT);

        impact_controller.attach(storage);
        impact_controller.attach(accelerometer);
        impact_controller.attach(gps);
        impact_controller.attach(environmental_sensor);

        impact_controller.create_impact();
        impact_controller.log_impact();

}

void loop() {
        acceleration_data acc = accelerometer->read();
        Serial.printf("%0.3f,%0.3f,%0.3f\n",
                acc.x,
                acc.y,
                acc.z);
        delay(1000);
}