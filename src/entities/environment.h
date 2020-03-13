#pragma once

#include "Arduino.h"

/*
 * environment - stores environmental sensor data.
 * @temperature
 * @humidity
 * @pressure
 * @altitude
 */
struct environment
{
        const float temperature;
        const float humidity;
        const float pressure;
        const float altitude;
};
