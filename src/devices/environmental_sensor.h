#pragma once

#include "Arduino.h"
#include "environmental_data.h"
// #include "Adafruit_Sensor.h"
// #include "Adafruit_BME_280.h"

class EnvironmentalSensor
{
        public:
                environmental_data *read();
        private:
                // Adafruit_BME_280 driver;
};