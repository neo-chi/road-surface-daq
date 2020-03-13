#pragma once

#include "Arduino.h"

/*
 * acceleration - stores accelerometer values.
 * @x acceleration
 * @y acceleration
 * @z acceleration
 */
struct acceleration
{
        const float x;
        const float y;
        const float z;
};
