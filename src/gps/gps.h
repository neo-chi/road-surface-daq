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
#include "datetime.h"
#include "location.h"

#define NAVIGATION_FREQ             3      // GPS sampling frequency
#define GPS_VEHICLE_IS_MOVING_SPEED 1000   // units: mm/s
#define GPS_NUM_CACHED_ITEMS        5

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
        MINUTE,
        SECOND
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

// TODO: description
class GPS
{
        public:
                GPS();
                void               begin();
                void               read();
                void               connect_to_satellites(long timeout = 0);
                bool               is_connected_to_satellites();
                enum vehicle_state get_vehicle_state();
                DateTime           datetime;
                Location           location;
                int32_t            vehicle_speed;
        private:
                SFE_UBLOX_GPS _driver;
                void          _start_driver();
                void          _initialize_datetime();
                void          _display_seconds_waiting();
                void          _set_cache_update_timers();
                void          _update_second();
                void          _update_minute();
                void          _update_hour();
                void          _update_day_month_year();
                void          _update_location();
                void          _update_vehicle_speed();
                long          _cache_update_timer[GPS_NUM_CACHED_ITEMS];
                bool          _cache_timers_set{false};
};
