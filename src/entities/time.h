#pragma once

#include "Arduino.h"

/*
 * time - stores gps time values.
 * @hour
 * @minute
 * @second
 * @millisecond
 */
struct time
{
        const uint8_t hour;
        const uint8_t minute;
        const uint8_t second;
        const uint8_t millisecond;
};
