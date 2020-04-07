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
        Serial.printf("complete!\n");
}

/**
 * Read GPS data.
 *
 * @returns gps_data
 **/
void IRAM_ATTR GPS::read()
{
        if (!cache_is_initialized) {
                Serial.printf("gps: initializing cache...");
                update_cache(YEAR);
                update_cache(MONTH);
                update_cache(DAY);
                update_cache(HOUR);
                update_cache(MINUTE);
                cache_is_initialized = true;
                Serial.printf("complete!\n");
        }
        Serial.println("gps: reading...");
        Serial.print("gps: reading from cache...");
        Serial.println("complete!");

        Serial.print("gps: reading second...");
        data.second = driver.getSecond();
        Serial.println("complete!");

        Serial.print("gps: reading millisecond...");
        data.millisecond = driver.getMillisecond();
        Serial.println("Complete!");

        Serial.print("gps: reading latitude...");
        data.latitude = driver.getLatitude();
        Serial.println("complete!");

        Serial.print("gps: reading longitude...");
        data.longitude = driver.getLongitude();
        Serial.println("complete!");

        Serial.print("gps: reading speed...");
        data.speed = driver.getGroundSpeed();
        Serial.println("complete!");
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
        if (this->is_connected_to_satellites()) {
                Serial.printf("gps: sattelites connected! %d satellites\n", driver.getSIV());
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

/**
 * Refreshes the cached gps data.
 *
 * @param gps_cache data to be refreshed.
 **/
void GPS::update_cache(gps_cache type)
{
        switch(type) {
        case YEAR:
                Serial.print("gps: updating cached year... ");
                data.year = driver.getYear();
                Serial.println("complete!");
                break;
        case MONTH:
                Serial.print("gps: updating cached month... ");
                data.month = driver.getMonth();
                Serial.println("complete!");
                break;
        case DAY:
                Serial.print("gps: updating cached day... ");
                data.day = driver.getDay();
                Serial.println("complete!");
                break;
        case HOUR:
                Serial.print("gps: updating cached hour... ");
                data.hour = driver.getHour();
                Serial.println("complete!");
                break;
        case MINUTE:
                Serial.print("gps: updating cached minute... ");
                data.minute = driver.getMinute();
                   Serial.println("complete!");
                break;
        default:
                Serial.println("gps: unhandled gps cache type!");
                break;
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
