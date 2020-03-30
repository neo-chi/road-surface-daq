/******************************************************************************
 * @file	environmental_sensor.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#include "environmental_sensor.h"

/**
 * Environmental Sensor Constructor
 *
 * @note the driver for this sensor will be configured during construction.
 *
 * @see	 /src/devices/environmental_sensor.cpp -> EnvironmentalSensor()
 * 		to configure this device.
 **/
EnvironmentalSensor::EnvironmentalSensor()
{
        //Wire.begin();
        //Serial.printf("initializing environmental sensor...\n");
	//Serial.printf("configuring...");
	//driver.setSampling();
	//driver.begin();
	//Serial.printf("complete!\n");
	//Serial.printf("initializing environmental sensor cache...");
        //if (!cache_is_initialized) {
                //update_cache();
                //cache_is_initialized = true;
        //}
	//Serial.printf("complete!\n");
	//Serial.printf("environmental sensor initialization complete!\n");
}

/**
 * Get the temperature, humidity, and pressure.
 *
 * @returns struct environmental_data
 **/
environmental_data EnvironmentalSensor::read()
{
        if (cache_is_initialized) {
                return cache;
        } else {
                update_cache();
                cache_is_initialized = true;
                return cache;
        }
}

/**
 * Refreshes environmental ata cache with current temperaute, humidity, and
 * 		pressure.
 * @note temperature:	degrees celcius
 * @note humidity:	%
 * @note pressure:	// [ ] add units for this
 */
void EnvironmentalSensor::update_cache()
{
        Serial.print("Updating environmental sensor cache... ");
        cache.temperature       = driver.readTemperature();
        cache.humidity          = driver.readHumidity();
        cache.pressure          = driver.readPressure();
        Serial.println("Complete!");
}
