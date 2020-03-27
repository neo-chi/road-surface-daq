#pragma once

#include "Arduino.h"

#include "accelerometer.h"
#include "environmental_sensor.h"
#include "gps.h"
#include "impact.h"
#include "storage.h"

class ImpactController
{
        public:
                ImpactController();
                const impact_data create_impact(gps_data gps,
                                          environmental_data environment,
                                          accelerometer_data *acceleration_buffer,
                                          int acceleration_buffer_length);
                void log_impact(Storage storage, impact_data impact);
                void upload_impact(const char *location);
        private:
                char *date_of(impact_data impact);
                char *time_of(impact_data impact);
                char *speed_of_vehicle_at(impact_data impact);
                char *location_of(impact_data impact);
                char *environment_of(impact_data impact);
                char **acceleration_response_of(impact_data impact);
                void append_to_log(char * message);
                char **log_buffer = (char **)malloc(2048 * sizeof(char));
                char **log_buffer_ptr_init = log_buffer;
                int log_buffer_length = 0;
};
