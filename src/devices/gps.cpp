// [ ]  GPS::vehicles_is_moving()
#include "gps.h"

/**
 * GPS constructor
 *
 * @returns GPS
 **/
GPS::GPS()
{
        Serial.println("Created a gps.");
}

/**
 * Read GPS data.
 *
 * @returns *gps_data
 **/
gps_data GPS::read()
{
        data = cache;
        data.second = 5;        // [ ] Read from driver
        data.millisecond = 6;   // [ ] Read from driver
        data.latitude = 7;      // [ ] Read from driver
        data.longitude = 8;     // [ ] Read from driver
        data.speed = 9;         // [ ] Read from driver
        return data;
}

/**
 * Attempt to get 3 satellite connections. Optional timeout timer.
 **/
void GPS::connect_to_satellites(long timeout)
{
        if (timeout == 0) {
                // attempt to connect forever
                long elapsed_time = 0;
                uint8_t seconds_waiting = 0;
                const int MAX_WAIT_SECONDS = 10;
                Serial.print("Waitng until satellite connection is received");
                while (!(this->is_connected_to_satellites())) {
                        if (seconds_waiting > MAX_WAIT_SECONDS) {
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
                long elapsed_time = 0;
                uint8_t seconds_waiting = 0;
                Serial.printf("Waiting %d milliseconds until satellite connection is received.");
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
        // [ ] GPS::is_connected_to_satellites()
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
        int speed = 1001; // [ ] remove me for driver implementation
        Serial.print("Checking vehicle movement state... ");
        if (is_connected_to_satellites()) {
                if (speed > 1000) {
                        Serial.println("Vehicle is moving!");
                        return moving;
                } else {
                        Serial.println("Vehicle is idle!");
                        return idle;
                }
        } else {
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
                cache.year = 2020;
                //> cache.year = driver.getYear();
                Serial.println("Complete!");
                break;
        case month:
                Serial.print("Updating cached month... ");
                cache.month = 1;
                //> cache.month = driver.getMonth();
                Serial.println("Complete!");
                break;
        case day:
                Serial.print("Updating cached day... ");
                cache.day = 2;
                //> cache.day = driver.getDay();
                Serial.println("Complete!");
                break;
        case hour:
                Serial.print("Updating cached hour... ");
                cache.hour = 3;
                //> cache.hour = driver.getHour();
                Serial.println("Complete!");
                break;
        case minute:
                Serial.print("Updating cached minute... ");
                cache.minute = 4;
                //> cache.minute = driver.getMinute();
                Serial.println("Complete!");
                break;
        default:
                Serial.println("Unhandled gps cache type!");
                break;
        }
}
