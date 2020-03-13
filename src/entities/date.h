#pragma once

#include "Arduino.h"

/*
 * date - stores gps date values.
 * @year
 * @month
 * @day
 */
struct date
{
        const uint16_t year;
        const uint8_t month;
        const uint8_t day;
};
