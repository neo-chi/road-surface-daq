/******************************************************************************
 * @file	gps.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#include "gps.h"
#include "Wire.h"

/**
 * GPS constructor
 *
 * @returns GPS
 **/
GPS::GPS()
{
}

/**
 * Enables the and configures the GPS driver.
 **/
void GPS::begin()
{
        Serial.printf("gps: initializing...");
        Wire.begin();
        driver.begin();
        driver.setI2COutput(COM_TYPE_UBX);
        driver.setNavigationFrequency(NAVIGATION_FREQ);
        driver.saveConfiguration();
        if (this->is_connected_to_satellites())
                __set_cache_update_timers();
        Serial.printf("complete!\n");
}

/**
 * Attempt to get 3 satellite connections. Optional timeout timer.
 *
 * @param timeout  optional maximum time to wait for a gps connection
 **/
void GPS::connect_to_satellites(long timeout)
{
        static const int DEFAULT_TIMEOUT  = 0;
        static long elapsed_time          = 0;
        if (timeout == DEFAULT_TIMEOUT) {
                Serial.println("gps: waiting until satellite connection is received...");
                while (!is_connected_to_satellites()) {
                        _display_seconds_waiting();
                }
        } else {
                Serial.printf("gps: waiting %d milliseconds for satellite connection...\n", timeout);
                while (millis() - elapsed_time < timeout && !is_connected_to_satellites()) {
                        _display_seconds_waiting();
                        elapsed_time = millis();
                }
        }
        if (is_connected_to_satellites()) {
                Serial.printf("gps: sattelites connected! %d satellites\n", driver.getSIV());
                if (!__cache_timers_set)
                        __set_cache_update_timers();
        } else {
                Serial.println("gps: could not connect to satellites!");
        }
}

/**
 * Check if GPS is connected to at least 3 satellites.
 *
 * @returns boolean
 **/
bool GPS::is_connected_to_satellites()
{
        uint8_t num_satellites = driver.getSIV();
        if (num_satellites > 2)
                return true;
        else
                return false;
}

/**
 * Check if the vehicle is moving at more than 1000 mm/s.
 *
 * @note The GPS *must* be connected to satellites for this
 * function to work.
 *
 * @returns vehicle state (idle, moving, unknown)
 **/
vehicle_state GPS::get_vehicle_state()
{
        Serial.print("gps: checking vehicle movement state...");
        if (is_connected_to_satellites()) {
                if (driver.getGroundSpeed() > GPS_VEHICLE_IS_MOVING_SPEED) { // 1 meter/second
                        Serial.println("vehicle is moving!");
                        return MOVING;
                } else {
                        Serial.println("vehicle is idle!");
                        return IDLE;
                }
        } else {
                Serial.println("no GPS satellite connection...vehicle state unknown!");
                return UNKNOWN;
        }

}

void GPS::_display_seconds_waiting()
{
        static const int  ONE_SECOND      = 1000;
        static       long elapsed_time    = 0;
        static       int  seconds_waiting = 0;
        if (seconds_waiting >= 3) {
                Serial.println();
                seconds_waiting = 0;
        }
        if (millis() - elapsed_time >= ONE_SECOND) {
                Serial.print(".");
                elapsed_time = millis();
                seconds_waiting++;
        }
}

void GPS::populate()
{
        __update_second();
        __update_minute();
        __update_hour();
        __update_day_month_year();
        __update_location();
        __update_vehicle_speed();
}

void GPS::__set_cache_update_timers()
{
        Serial.println("gps: set cache update timers");
        __cache_update_timer[SECOND] = SECOND_MILLIS - (long)(driver.getMillisecond());
        __cache_update_timer[MINUTE] = MINUTE_MILLIS - (long)(driver.getSecond() * SECOND_MILLIS);
        __cache_update_timer[HOUR]   = HOUR_MILLIS   - (long)(driver.getMinute() * MINUTE_MILLIS);
        __cache_update_timer[DAY]    = DAY_MILLIS    - (long)(driver.getHour()   * HOUR_MILLIS);
        datetime.set_year(driver.getYear());
        datetime.set_month(driver.getMonth());
        datetime.set_day(driver.getDay());
        datetime.set_hour(driver.getHour());
        datetime.set_minute(driver.getMinute());
        datetime.set_second(driver.getSecond());
        __cache_timers_set = true;
}

void GPS::__update_second()
{
        static long elapsed_time{__cache_update_timer[SECOND]};
        if (millis() - elapsed_time >= SECOND_MILLIS) {
                Serial.println("updated second"); // TODO: remove me
                datetime.set_second(driver.getSecond());
                elapsed_time = millis();
        }
}

void GPS::__update_minute()
{
        static long elapsed_time{__cache_update_timer[MINUTE]};
        if (millis() - elapsed_time >= MINUTE_MILLIS) {
                Serial.println("updated minute"); // TODO: remove me
                datetime.set_minute(driver.getMinute());
                elapsed_time = millis();
        }
}

void GPS::__update_hour()
{
        static long elapsed_time{__cache_update_timer[HOUR]};
        if (millis() - elapsed_time >= HOUR_MILLIS) {
                Serial.println("updated hour"); // TODO: remove me
                datetime.set_hour(driver.getHour());
                elapsed_time = millis();
        }
}

void GPS::__update_day_month_year()
{
        static long elapsed_time{__cache_update_timer[DAY]};
        if (millis() - elapsed_time >= DAY_MILLIS) {
                datetime.set_day(driver.getDay());
                datetime.set_month(driver.getMonth());
                datetime.set_year(driver.getYear());
                elapsed_time = millis();
        }
}

void GPS::__update_location()
{
        location.set_location(driver.getLatitude(), driver.getLongitude());
}

void GPS::__update_vehicle_speed()
{
        vehicle_speed = driver.getGroundSpeed();
}
