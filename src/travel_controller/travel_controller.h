#pragma once

#include "Arduino.h"
#include "environmental_sensor.h"
#include "gps.h"
#include "storage.h"
#include "wifi.h"
#include "HTTPClient.h"

#define TRAVEL_LOG_SIZE_MAX 10240
#define TRAVEL_NUMBER_OF_LOGS_MAX 60

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

class TravelController
{
        public:
                TravelController();
                void                    attach(Storage *storage);
                void                    attach(GPS *gps);
                void                    attach(EnvironmentalSensor *environmental_sensor);
                void                    attach(WiFiManager *wifi);
                void                    create_travel();
                void                    log_travel();
                void                    upload_travel(const char *location);
                bool                    buffer_is_full();
        private:
                Storage                 *storage;
                GPS                     *gps;
                EnvironmentalSensor     *environmental_sensor;
                WiFiManager             *wifi;
                travel_data             travel;
                travel_data             travel_buffer[TRAVEL_NUMBER_OF_LOGS_MAX];
                int                     number_of_travel_logs = 0;
                size_t                  offset = 0;
                char                    log_dir[16];
                char                    log_filename[16];  // 8.3 format
                char                    path[32];
                char                    log[TRAVEL_LOG_SIZE_MAX];
                void                    _write_travel_log();
                void                    _log_travel_date(int travel_buffer_index);
                void                    _log_travel_time(int travel_buffer_index);
                void                    _log_travel_location(int travel_buffer_index);
                void                    _log_travel_vehicle_speed(int travel_buffer_index);
                void                    _log_travel_environment(int travel_buffer_index);
                void                    _generate_log_directory();
                void                    _generate_log_filename();
                void                    _extend_offset(size_t number_of_bytes);
                void                    _reset_offset();
};
