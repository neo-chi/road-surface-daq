#include "environment.h"

/**
 * Default constructor
 *
 * @returns Environment
 **/
Environment::Environment()
{
        // nothing to do here...
}

Environment::~Environment()
{
        // nothing to do here...
}

char *Environment::to_string()
{
        char result[64];
        sprintf(result, "%0.4f,%0.4f,%0.4f", *temperature, *humidity, *pressure);
        return result;
}

void Environment::set_environment(float temperature, float humidity, float pressure)
{
        set_temperature(temperature);
        set_humidity(humidity);
        set_pressure(pressure);
}

/**
 * Points this environment's temperature, humidity, to input addresses.
 * When the source's environment is updated, this object's environment will automatically
 * reflect these changes.
 *
 * @param temperature  pointer
 * @param humidity pointer
 * @param pressure   pointer
 **/
void Environment::link_environment(float *temperature, float *humidity, float *pressure)
{
        if (temperature != NULL)
                this->temperature = temperature;
        if (humidity != NULL)
                this->humidity = humidity;
        if (pressure != NULL)
                this->pressure = pressure;
}

void Environment::set_temperature(float temperature)
{
        *this->temperature = temperature;
}

void Environment::set_humidity(float humidity)
{
        *this->humidity = humidity;
}

void Environment::set_pressure(float pressure)
{
        *this->pressure = pressure;
}

float Environment::get_temperature()
{
        return *temperature;
}

float Environment::get_humidity()
{
        return *humidity;
}

float Environment::get_pressure()
{
        return *pressure;
}
