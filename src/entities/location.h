/*******************************************************************************
 * @file	location.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * Encapsulate gps location data:
 *      - latitude
 *      - longitude
 * Print location data in csv format:
 *      "latitude, longitude"
*******************************************************************************/

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
                int32_t *_latitude {(int32_t*)malloc(sizeof(int32_t))};
                int32_t *_longitude{(int32_t*)malloc(sizeof(int32_t))};
};