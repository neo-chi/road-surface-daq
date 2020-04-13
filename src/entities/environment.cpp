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
        sprintf(result, "%0.4f,%0.4f,%0.4f", *_temperature, *_humidity, *_pressure);
        return result;
}

void Environment::set_environment(float temperature, float humidity, float pressure)
{
        set_temperature(temperature);
        set_humidity(humidity);
        set_pressure(pressure);
}

void Environment::set_temperature(float temperature)
{
        *this->_temperature = temperature;
}

void Environment::set_humidity(float humidity)
{
        *this->_humidity = humidity;
}

void Environment::set_pressure(float pressure)
{
        *this->_pressure = pressure;
}

float Environment::get_temperature()
{
        return *_temperature;
}

float Environment::get_humidity()
{
        return *_humidity;
}

float Environment::get_pressure()
{
        return *_pressure;
}
