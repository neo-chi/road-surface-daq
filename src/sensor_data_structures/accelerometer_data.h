#pragma once

#include "Arduino.h"

#define SIZE_ACCELEROMETER_BUFFER 512


struct accelerometer_data {
        float x;
        float y;
        float z;
};
