#pragma once

#include "Arduino.h"

class Time
{
        public:
                Time();
                ~Time();
                char   *to_string();
                void    set_time(uint8_t hour, uint8_t minute, uint8_t second);
                void    link_time(uint8_t *hour, uint8_t *minute, uint8_t *second);
                void    set_hour(uint8_t hour);
                void    set_minute(uint8_t hour);
                void    set_second(uint8_t second);
                uint8_t get_hour();
                uint8_t get_minute();
                uint8_t get_second();
        protected:
                uint8_t  *hour   = (uint8_t*)malloc(sizeof(uint8_t));
                uint8_t  *minute = (uint8_t*)malloc(sizeof(uint8_t));
                uint8_t  *second = (uint8_t*)malloc(sizeof(uint8_t));
};