#include "environmental_sensor.h"

/**
 * Environmental Sensor Constructor
 **/
EnvironmentalSensor::EnvironmentalSensor()
{
        Serial.println("Created an environmental sensor.");
        if (!cache_is_initialized) {
                update_cache();
                cache_is_initialized = true;
        }
}

/**
 * Get this sensor's data as a structure
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
 * Refreshes environmental data cache with current values.
 **/
void EnvironmentalSensor::update_cache()
{
        Serial.print("Updating environmental sensor cache... ");
        cache.temperature       = 1;
        cache.humidity          = 2;
        cache.pressure          = 3;
        cache.altitude          = 4;
        Serial.println("Complete!");
}
