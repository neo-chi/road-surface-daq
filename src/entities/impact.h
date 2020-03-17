#pragma once

#include "Arduino.h"

struct impact_data {
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
        float speed;
        struct {
                float temperature;
                float humidity;
                float pressure;
                float altitude;
        };
        //AccelerometerDataBuffer *acceleration_buffer;
};
