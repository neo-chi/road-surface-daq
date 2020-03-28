#include <Arduino.h>

#include "accelerometer.h"
#include "gps.h"

Accelerometer accelerometer;
GPS gps;

void setup()
{
        delay(1000);  // UNIX
        Serial.begin(9600);

        gps_data dat = gps.read();
        Serial.println(dat.year);
        Serial.println(dat.month);
        Serial.println(dat.day);
        Serial.println(dat.hour);
        Serial.println(dat.minute);
        Serial.println(dat.second);
        Serial.println(dat.millisecond);
        Serial.println(dat.latitude);
        Serial.println(dat.longitude);
        Serial.println(dat.speed);


        accelerometer.begin();

}

void loop() {
        acceleration_data acc = accelerometer.read();
        Serial.println(acc.x);
        Serial.println(acc.y);
        Serial.println(acc.z);
        //gps_data dat = gps.read();
        //Serial.println(dat.year);
        //Serial.println(dat.month);
        //Serial.println(dat.day);
        //Serial.println(dat.hour);
        //Serial.println(dat.minute);
        //Serial.println(dat.second);
        //Serial.println(dat.millisecond);
        //Serial.println(dat.latitude);
        //Serial.println(dat.longitude);
        //Serial.println(dat.speed);
        delay(1000);
}