/******************************************************************************
 * @file	environmental_sensor.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * The env sensor class defines the implementation specific behaviours for
 * the env sensor used in this project. A driver library must be included
 * and constructed in the private member "driver" of this class in order for
 * this class to function properly.
 *
 * This class features:
 *      - temperature, humidity and pressure cache
 *      - evnrionmental data structure storing the above data
 *
 * The BME280 env sensor was selected for this design, and the supporting
 * driver library by Adafruit, "Adafruit_BME280" is used to in this
 * initial implementationk.
*******************************************************************************/
#pragma once

#include "Arduino.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"
#include "Wire.h"
#include "environment.h"

class EnvironmentalSensor
{
        public:
                EnvironmentalSensor();
                void  begin();
                void  read();
                Environment environment;
        private:
                Adafruit_BME280 _driver;
};
