#pragma once

#include "Arduino.h"

#include "accelerometer.h"
#include "environmental_sensor.h"
#include "gps.h"
#include "impact.h"
#include "storage.h"

#define LOG_SIZE_MAX 40000


class ImpactController
{
        public:
                ImpactController();
                ImpactController(Storage *storage, Accelerometer *accelerometer, GPS *gps, EnvironmentalSensor *environmental_sensor);
                void create_impact();
                void log_impact();
                void upload_impact(const char *location);
                void attach(Storage *storage);
                void attach(Accelerometer *accelerometer);
                void attach(GPS *gps);
                void attach(EnvironmentalSensor *environmental_sensor);

                char log_dir[16];
                char log_filename[16];  // 8.3 format
                char path[32];
                //char date[16];      // YYYYMMDD
                //char time[32];      // HHMMSSss
                //char location[32];  // latitude,longitude
                //char speed[16];          // speed
                //char environment[64];
                //char acceleration[50000]; // or char *acceleration...

                impact_data impact;
                char log[LOG_SIZE_MAX];
                size_t offset = 0;

        private:
                Storage *storage;
                Accelerometer *accelerometer;
                GPS *gps;
                EnvironmentalSensor *environmental_sensor;
                void append_to_log(char *message);
                void reset_offset();
                void extend_offset(size_t number_of_bytes);

};
