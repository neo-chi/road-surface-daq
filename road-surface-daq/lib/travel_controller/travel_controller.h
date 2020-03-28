#pragma once

#include "Arduino.h"

#include "environmental_sensor.h"
#include "gps.h"
#include "storage.h"

/**
 * Aggregates data relevant to recording and analysing healthy roads.
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
 * @temperature
 * @humidity
 * @pressure
 **/

struct travel_data {
        struct {
                uint16_t        year;
                uint8_t         month;
                uint8_t         day;
        };
        struct {
                uint8_t         hour;
                uint8_t         minute;
                uint8_t         second;
                uint8_t         millisecond;
        };
        struct {
                float           latitude;
                float           longitude;
        };
        struct {
                float           temperature;
                float           humidity;
                float           pressure;
        };
        float                   speed;
};

#define TRAVEL_LOG_BUFFER_LEN 512

class TravelController
{
        public:
                TravelController();
                travel_data create_travel(gps_data gps,
                                          environmental_data environment);
                void log_travel(Storage storage);
                void upload_travel(String location);
                bool buffer_is_full();
        private:
                char *date_of(travel_data travel);
                char *time_of(travel_data travel);
                char *speed_of(travel_data travel);
                char *location_of(travel_data travel);
                char *environment_of(travel_data travel);
                void append_to_log_buffer(travel_data travel);
                void reset_log_buffer_head();
                void increment_log_buffer_index();
                char *log_buffer[TRAVEL_LOG_BUFFER_LEN];
                int log_buffer_length = TRAVEL_LOG_BUFFER_LEN;
                int log_buffer_index = 0;
};
