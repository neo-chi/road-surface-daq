#pragma once

#include "Arduino.h"

#define SIZE_ACCELEROMETER_BUFFER 512

/**
 * Aggregates accelerometer data.
 *
 * @x acceleration
 * @y acceleration
 * @z acceleration
 */
struct accelerometer_data {
        float x;
        float y;
        float z;
};
