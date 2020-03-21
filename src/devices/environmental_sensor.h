#pragma once

#include "Arduino.h"
#include "environmental_data.h"
// #include "Adafruit_Sensor.h"
// #include "Adafruit_BME_280.h"

class EnvironmentalSensor
{
        public:
                EnvironmentalSensor();
                environmental_data read();
                void update_cache();
        private:
                // Adafruit_BME_280 driver;
                bool cache_is_initialized = false;
                environmental_data cache;
};
