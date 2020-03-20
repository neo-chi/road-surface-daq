#pragma once

#include "Arduino.h"

struct travel_data {
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
        float speed;
};
