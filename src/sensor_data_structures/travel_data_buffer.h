#pragma once

#include "Arduino.h"
#include "travel.h"

#define SIZE_TRAVEL_BUFFER 512

class TravelDataBuffer {
        public:
                void push(travel_data);
                travel_data pop();
                bool is_full();
                void flush();
                int size();
        private:
                travel_data buffer[SIZE_TRAVEL_BUFFER];
                int buffer_size = SIZE_TRAVEL_BUFFER;
};
