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
                travel_data create_travel(gps_data *gps,
                                   environmental_data *environment);
                void log_travel(Storage storage, TravelDataBuffer *travel_buffer);
                void upload_travel(String location);
        private:
                TravelDataBuffer *buffer;
};
