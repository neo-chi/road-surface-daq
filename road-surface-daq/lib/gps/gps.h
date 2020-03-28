/******************************************************************************
 * @file	gps.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-24
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#pragma once

#include "Arduino.h"
#include "SparkFun_Ublox_Arduino_Library.h"

/**
 * Specifies the data to be cached by the gps.
 *
 * @year
 * @month
 * @day
 * @hour
 * @minute
 **/
enum gps_cache {
        year,
        month,
        day,
        hour,
        minute
};

/**
 * Specifies the possible vehicle movement states.
 *
 * @idle
 * @moving
 * @unknown if the gps is not connected to satellites.
 **/
enum vehicle_state {
        idle,
        moving,
        unknown
};

/**
 * Aggregates relevant gps data.
 *
 * @year
 * @month
 * @day
 * @hour
 * @minute
 * @second
 * @millisecond
 * @latitude
 * @longitude
 * @speed
 **/
struct gps_data {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint16_t second;
        uint16_t millisecond;
        int32_t latitude;
        int32_t longitude;
        int32_t speed;
};

class GPS
{
        public:
                GPS();
                gps_data        read();
                void            connect_to_satellites(long timeout = 0);
                bool            is_connected_to_satellites();
                enum            vehicle_state vehicle_state();
                void            update_cache(gps_cache type);
        private:
                SFE_UBLOX_GPS   driver;
                bool            cache_is_initialized = false;
                gps_data        data;
                gps_data        cache;
};
