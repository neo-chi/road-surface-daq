#pragma once

#include "Arduino.h"

class Location
{
        public:
                Location();
                ~Location();
                char   *to_string();
                void    set_location(int32_t latitude, int32_t longitude);
                void    link_location(int32_t *latitude, int32_t *longitude);
                int32_t set_latitude(int32_t latitude);
                int32_t set_longitude(int32_t longitude);
                int32_t get_latitude();
                int32_t get_longitude();
        protected:
                int32_t *latitude  = (int32_t*)malloc(sizeof(int32_t));
                int32_t *longitude = (int32_t*)malloc(sizeof(int32_t));
};