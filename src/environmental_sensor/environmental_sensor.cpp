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
        // nothing to do here...
}

/**
 * Enables the environmental sensor _driver and configures this environmental
 * sensor.
 **/
void EnvironmentalSensor::begin()
{
        Wire.begin();
        Serial.printf("env sensor: initializing...\n");
        Serial.printf("env sensor: configuring...");
        _driver.begin();
        _driver.setSampling();
        Serial.printf("complete!\n");
        Serial.printf("env sensor: complete!\n");
}

/**
 * Get the temperature, humidity, and pressure.
 **/
void EnvironmentalSensor::read()
{
        Serial.printf("env sensor: reading from cache...");
        environment.set_environment(
                _driver.readTemperature(),
                _driver.readHumidity(),
                _driver.readPressure()
        );
        Serial.printf("complete!\n");
}
