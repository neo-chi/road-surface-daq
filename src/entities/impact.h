#pragma once

#include "Arduino.h"

/**
 * The impact_data structure aggregates all of the data important to recording
 * and analyzing an impact event.
 *
 * @speed
 * @*acceleration_buffer
 * @year
 * @month
 * @day
 * @hour
 * @minute
 * @second
 * @millisecond
 * @latitude
 * @longitude
 * @temperature
 * @humidity
 * @pressure
 * @altitude
 **/
struct impact_data {
        float               speed;
        accelerometer_data *acceleration_buffer;
        int                 acceleration_buffer_length;
        struct {
                uint16_t year;
                uint8_t month;
                uint8_t day;
        };
        struct {
                uint8_t hour;
                uint8_t minute;
                uint8_t second;
                uint8_t millisecond;
        };
        struct {
                float latitude;
                float longitude;
        };
        struct {
                float temperature;
                float humidity;
                float pressure;
                float altitude;
        };
};
