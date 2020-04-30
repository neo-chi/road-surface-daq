/*******************************************************************************
 * @file	date.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * Encapsulate GPS date data and allows printing in the format "YYYY-MM-DD".
*******************************************************************************/

#pragma once

#include "Arduino.h"

class Date
{
        public:
                Date();
                ~Date();
                char    *to_string();
                void     set_date(uint16_t year, uint8_t month, uint8_t day);
                void     set_year(uint16_t year);
                void     set_month(uint8_t month);
                void     set_day(uint8_t day);
                uint16_t get_year();
                uint8_t  get_month();
                uint8_t  get_day();
        protected:
                uint16_t *_year {(uint16_t*)malloc(sizeof(uint16_t))};
                uint8_t  *_month{(uint8_t*)malloc(sizeof(uint8_t))};
                uint8_t  *_day  {(uint8_t*)malloc(sizeof(uint8_t))};
};
