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
 * @note call begin() on this environmental sensor enable it.
 **/
EnvironmentalSensor::EnvironmentalSensor()
{
}

/**
 * Enables the environmental sensor driver and configures this environmental
 * sensor.
 **/
void EnvironmentalSensor::begin()
{
        Wire.begin();
        Serial.printf("env sensor: initializing...\n");
        Serial.printf("env sensor: configuring...");
        driver.begin();
        driver.setSampling();
        Serial.printf("complete!\n");
        Serial.printf("env sensor: initializing cache...");
        if (!cache_is_initialized) {
                update_cache();
                cache_is_initialized = true;
        }
        Serial.printf("complete!\n");
        Serial.printf("env sensor: complete!\n");
}

/**
 * Get the temperature, humidity, and pressure.
 **/
void EnvironmentalSensor::read()
{
        Serial.printf("env sensor: reading from cache...");
        data.temperature       = driver.readTemperature();
        data.humidity          = driver.readHumidity();
        data.pressure          = driver.readPressure();
        Serial.printf("complete!\n");
}

/**
 * Refreshes environmental data cache with current temperaute, humidity, and
 * 		pressure.
 * @note temperature:	degrees celcius
 * @note humidity:	%
 * @note pressure:	hPA
 */
void EnvironmentalSensor::update_cache()
{
        Serial.print("env sensor: updating cache... ");
        data.temperature       = driver.readTemperature();
        data.humidity          = driver.readHumidity();
        data.pressure          = driver.readPressure();
        Serial.printf("complete!\n");
}

void EnvironmentalSensor::populate()
{
        temperature = driver.readTemperature();
        humidity    = driver.readHumidity();
        pressure    = driver.readPressure();
}
