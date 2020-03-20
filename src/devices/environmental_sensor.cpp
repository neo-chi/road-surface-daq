#include "environmental_sensor.h"

/**
 * Environmental Sensor Constructor
 *
 //* @returns EnvironmentSensor
 */
EnvironmentalSensor::EnvironmentalSensor()
{
        Serial.println("Created an environmental sensor.");
}

/**
 * Get this sensor's data as a structure
 *
 * @returns struct environmental_data
 */
environmental_data EnvironmentalSensor::read()
{
        Serial.print("Reading environmental sensor... ");
        environmental_data env_data;
        env_data.temperature = 1;
        env_data.humidity = 2;
        env_data.pressure = 3;
        env_data.altitude = 4;
        Serial.println("Complete!");
        return env_data;
}
