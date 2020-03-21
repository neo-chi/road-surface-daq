#pragma once

#include "Arduino.h"

/**
 * Aggregates environmental sensor data.
 *
 * @temperature
 * @humidity
 * @pressure
 * @altitude
 **/
struct environmental_data {
        float temperature;
        float humidity;
        float pressure;
        float altitude;
};