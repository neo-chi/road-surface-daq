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
        uint8_t second;
        uint8_t millisecond;
        float latitude;
        float longitude;
        float speed;
};
