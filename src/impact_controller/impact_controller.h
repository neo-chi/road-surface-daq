#pragma once

#include "Arduino.h"
#include "accelerometer.h"
#include "environmental_sensor.h"
#include "gps.h"
#include "storage.h"
#include "wifi.h"
#include "HTTPClient.h"

#define IMPACT_LOG_SIZE_MAX 32000

class ImpactController
{
        public:
                ImpactController();
                void                    attach(Storage *storage);
                void                    attach(Accelerometer *accelerometer);
                void                    attach(GPS *gps);
                void                    attach(EnvironmentalSensor *environmental_sensor);
                void                    attach(WiFiManager *wifi);
                void                    create_impact();
                void                    log_impact();
                void                    log_acceleration();
                void                    upload_impact(const char *location);
        private:
                Storage                 *storage;
                Accelerometer           *accelerometer;
                GPS                     *gps;
                EnvironmentalSensor     *environmental_sensor;
                WiFiManager             *wifi;
                impact_data             impact;
                size_t                  offset = 0;
                char                    log_dir[16];
                char                    log_filename[16];  // 8.3 format
                char                    path[32];
                char                    log[IMPACT_LOG_SIZE_MAX];
                void                    _log_impact_date();
                void                    _log_impact_time();
                void                    _log_impact_location();
                void                    _log_impact_vehicle_speed();
                void                    _log_impact_environment();
                void                    _log_impact_acceleration();
                void                    _generate_log_directory();
                void                    _generate_log_filename();
                void                    _write_impact_log();
                void                    _write_acceleration_log();
                void                    _extend_offset(size_t number_of_bytes);
                void                    _reset_offset();
};
