/*******************************************************************************
 * @file	_time.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * Encapsulates GPS time data and allows printing time in the form "HH:MM:SS".
*******************************************************************************/

#pragma once

#include "Arduino.h"

class Time
{
        public:
                Time();
                ~Time();
                char   *to_string();
                void    set_time(uint8_t hour, uint8_t minute, uint8_t second);
                void    set_hour(uint8_t hour);
                void    set_minute(uint8_t hour);
                void    set_second(uint8_t second);
                uint8_t get_hour();
                uint8_t get_minute();
                uint8_t get_second();
        protected:
                uint8_t  *_hour  {(uint8_t*)malloc(sizeof(uint8_t))};
                uint8_t  *_minute{(uint8_t*)malloc(sizeof(uint8_t))};
                uint8_t  *_second{(uint8_t*)malloc(sizeof(uint8_t))};
};