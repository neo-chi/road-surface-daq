/******************************************************************************
 * @file	environmental_sensor.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#pragma once

#include "Arduino.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"
#include "Wire.h"

/**
 * Environmental sensor possible data readings.
 *
 * @temperature  degrees celcius
 * @humidity     %
 * @pressure     // [ ] add units for this
 **/
struct environmental_data {
        float temperature;
        float humidity;
        float pressure;
};

class EnvironmentalSensor
{
        public:
                EnvironmentalSensor();
                Adafruit_BME280		driver;
                environmental_data	read();
                void			update_cache();
        private:
                environmental_data	cache;
                bool			cache_is_initialized = false;
};
