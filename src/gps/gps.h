/******************************************************************************
 * @file	gps.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-24
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * The gps class defines the implementation specific behaviours for the GPS
 * used in this project. A driver library must be included and constructed in
 * the private member "driver" of this class for this class to function
 * properly.
 *
 * This class features:
 *      - GPS satellite connection verification and wait functions
 *      - GPS data cache including:
 *              - year
 *              - month
 *              - day
 *              - hour
 *              - minute
 *      - Burst reads of date, time, location, and vehicle speed returned in
 *              a structure.
 *      - Vehicle state identification:
 *              - IDLE
 *              - MOVING
 *              - UNKNOWN
 *
 * The ZOE-M8Q GPS was selected for this design, and the supporting
 * driver library by Sparfun, "SparkFun_Ublox_Arduino_Library" is used to in
 * this initial implementation.
*******************************************************************************/
#pragma once

#include "Arduino.h"
#include "SparkFun_Ublox_Arduino_Library.h"

#define NAVIGATION_FREQ             3     // GPS sampling frequency
#define GPS_VEHICLE_IS_MOVING_SPEED 1000   // units: mm/s

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
        YEAR,
        MONTH,
        DAY,
        HOUR,
        MINUTE
};

/**
 * Specifies the possible vehicle movement states.
 *
 * @idle
 * @moving
 * @unknown if the gps is not connected to satellites.
 **/
enum vehicle_state {
        IDLE,
        MOVING,
        UNKNOWN
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
                void            begin();
                void            read();
                void            connect_to_satellites(long timeout = 0);
                bool            is_connected_to_satellites();
                enum            vehicle_state get_vehicle_state();
                void            update_cache(gps_cache type);
                gps_data        data;
        private:
                SFE_UBLOX_GPS   driver;
                bool            cache_is_initialized = false;
                void            _display_seconds_waiting();
};
