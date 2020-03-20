#pragma once

#include "Arduino.h"

#include "environmental_data.h"
#include "gps_data.h"
#include "storage.h"
#include "travel.h"
#include "travel_data_buffer.h"

class TravelController
{
        public:
                TravelController();
                travel_data create_travel(gps_data gps,
                                          environmental_data environment);
                void log_travel(Storage storage);
                void upload_travel(String location);
        private:
                char *date_of(travel_data travel);
                char *time_of(travel_data travel);
                char *speed_of(travel_data travel);
                char *location_of(travel_data travel);
                char *environment_of(travel_data travel);
                void append_to_log_buffer(travel_data travel);
                void reset_log_buffer_head();
                void increment_log_buffer_length();
                char **log_buffer = (char**)malloc(2048 * sizeof(char));
                char ** log_buffer_ptr_initial;
                int log_buffer_length = 0;
};
