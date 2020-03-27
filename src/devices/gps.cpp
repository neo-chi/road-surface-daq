/******************************************************************************
 * @file	gps.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#include "gps.h"
#include "Wire.h"

#define NAVIGATION_FREQ 3

/**
 * GPS constructor
 *
 * @returns GPS
 **/
GPS::GPS()
{
        Wire.begin();
        driver.begin();
        driver.setI2COutput(COM_TYPE_UBX);
        driver.setNavigationFrequency(NAVIGATION_FREQ);
        driver.saveConfiguration();
        Serial.println("Created a gps.");
}

/**
 * Read GPS data.
 *
 * @returns *gps_data
 **/
gps_data GPS::read()
{
        if (!cache_is_initialized) {
                update_cache(year);
                update_cache(month);
                update_cache(day);
                update_cache(hour);
                update_cache(minute);
                cache_is_initialized = true;
                Serial.println("Cache initialized!");
        }
        Serial.println("Reading gps...");
        Serial.print("Reading from cache...");
        data = cache;
        Serial.println("Complete!");

        Serial.print("Reading second ...");
        data.second = driver.getSecond();
        Serial.println("Complete!");

        Serial.print("Reading millisecond...");
        data.millisecond = driver.getMillisecond();
        Serial.println("Complete!");

        Serial.print("Reading latitude...");
        data.latitude = driver.getLatitude();
        Serial.println("Complete!");

        Serial.print("Reading longitude...");
        data.longitude = driver.getLongitude();
        Serial.println("Complete!");

        Serial.print("Reading speed...");
        data.speed = driver.getGroundSpeed();
        Serial.println("Complete!");
        return data;
}

/**
 * Attempt to get 3 satellite connections. Optional timeout timer.
 **/
void GPS::connect_to_satellites(long timeout)
{
        if (timeout == 0) {
                // attempt to connect forever
                long            elapsed_time            = 0;
                uint8_t         seconds_waiting         = 0;
                const int       MAX_WAIT_SECONDS        = 10;
                Serial.print("Waiting until satellite connection is received");
                while (!(this->is_connected_to_satellites())) {
                        if (seconds_waiting >= MAX_WAIT_SECONDS) {
                                seconds_waiting = 0;
                                Serial.println();
                        }
                        if (millis() - elapsed_time > 1000) {
                                Serial.print(".");
                                elapsed_time = millis();
                                seconds_waiting++;
                        }

                }
        } else {
                long            elapsed_time            = 0;
                uint8_t         seconds_waiting         = 0;
                Serial.printf("Waiting %d milliseconds until satellite connection is received.", timeout);
                while (millis() - elapsed_time < timeout) {
                        if (seconds_waiting >= 3)
                                Serial.printf("\b\b\b");
                        if (millis() - elapsed_time > 1000) {
                                Serial.print(".");
                                elapsed_time = millis();
                                seconds_waiting++;
                        }
                }
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
        //Serial.printf("Connected to %d satellites\n", num_satellites);
        if (num_satellites > 2)
                return true;
        else
                return false;
}

/**
 * Check if the vehicle is moving at more than 1000 mm/s.
 *
 * The GPS *must* be connected to satellites for this
 * function to work.
 *
 * @returns boolean
 **/
vehicle_state GPS::vehicle_state()
{
        Serial.print("Checking vehicle movement state... ");
        if (is_connected_to_satellites()) {
                if (data.speed > 1000) { // 1 meter/second
                Serial.println("Vehicle is moving!");
                        return moving;
                } else {
                        Serial.println("Vehicle is idle!");
                        return idle;
                }
        } else {
                Serial.println("No GPS connection. Vehicle state unknown!");
                return unknown;
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
        case year:
                Serial.print("Updating cached year... ");
                cache.year = driver.getYear();
                Serial.println("Complete!");
                break;
        case month:
                Serial.print("Updating cached month... ");
                cache.month = driver.getMonth();
                Serial.println("Complete!");
                break;
        case day:
                Serial.print("Updating cached day... ");
                cache.day = driver.getDay();
                Serial.println("Complete!");
                break;
        case hour:
                Serial.print("Updating cached hour... ");
                cache.hour = driver.getHour();
                Serial.println("Complete!");
                break;
        case minute:
                Serial.print("Updating cached minute... ");
                cache.minute = driver.getMinute();
                Serial.println("Complete!");
                break;
        default:
                Serial.println("Unhandled gps cache type!");
                break;
        }
}
