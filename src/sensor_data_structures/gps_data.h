#pragma once

#include "Arduino.h"

/**
 * Aggregates relevant gps data.
 *
 * @year
 * @month
 * @day
 * @hour
 * @minute
 * @second
 * @millisecond
 * @latitude
 * @longitude
 * @speed
 **/
struct gps_data {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint16_t second;
        uint16_t millisecond;
        int32_t latitude;
        int32_t longitude;
        int32_t speed;
};
