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
        // nothing to do here...
}

/**
 * Enables the and configures the GPS driver.
 **/
void GPS::begin()
{
        /* DEBUG */     Serial.printf("gps: initializing...");//FIXME: move to debugger
        _start_driver();
        if (this->is_connected_to_satellites()) {
                _set_cache_update_timers();
                _initialize_datetime();
        }
        /* DEBUG */     Serial.printf("complete!\n");//FIXME: move to debugger
}

void IRAM_ATTR GPS::read()
{
        if (this->is_connected_to_satellites()) {
                _update_second();
                _update_minute();
                _update_hour();
                _update_day_month_year();
                _update_location();
                _update_vehicle_speed();
        }
}

/**
 * Attempt to get 3 satellite connections. Optional timeout timer.
 *
 * @param timeout  optional maximum time to wait for a gps connection
 **/
void IRAM_ATTR GPS::connect_to_satellites(long timeout)
{
        static const int DEFAULT_TIMEOUT{0};
        static long      elapsed_time   {0};

        if (timeout == DEFAULT_TIMEOUT) {
                /* DEBUG */     Serial.println("gps: waiting until satellite connection is received...");//FIXME: move to debugger
                while (!this->is_connected_to_satellites()) {
                        _display_seconds_waiting();
                }
        }

        if (timeout != DEFAULT_TIMEOUT) {
                /* DEBUG */     Serial.println("gps: waiting until satellite connection is received...");//FIXME: move to debugger
                // /* DEBUG */     Serial.printf("gps: waiting %d milliseconds for satellite connection...\n", timeout);//FIXME: move to debugger
                while (millis() - elapsed_time < timeout
                       && !this->is_connected_to_satellites()) {
                        _display_seconds_waiting();
                        elapsed_time = millis();
                }
        }

        if (this->is_connected_to_satellites()) {
                /* DEBUG */     Serial.printf("gps: sattelites connected! %d satellites\n", _driver.getSIV());//FIXME: move to debugger
                if (!_cache_timers_set) {
                        _set_cache_update_timers();
                        _initialize_datetime();
                }
        } else {
                /* DEBUG */     Serial.println("gps: could not connect to satellites!");//FIXME: move to debugger
        }
}

/**
 * Check if GPS is connected to at least 3 satellites.
 *
 * @returns boolean
 **/
bool IRAM_ATTR GPS::is_connected_to_satellites()
{
        const uint8_t num_satellites{_driver.getSIV()};
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
        if (this->is_connected_to_satellites()) {
                if (_driver.getGroundSpeed() > GPS_VEHICLE_IS_MOVING_SPEED) {
                        Serial.println("vehicle state: MOVING");
                        return MOVING;
                } else {
                        Serial.println("vehicle state: IDLE");
                        return IDLE;
                }
        } else {
                Serial.println("vehicle state: UNKNOWN");
                return UNKNOWN;
        }
}

// TODO: description
void GPS::_set_cache_update_timers()
{
        /* DEBUG */     Serial.print("gps: setting cache update timers...");//FIXME: move to debugger
        _cache_update_timer[SECOND]
                = SECOND_MILLIS - (long)(_driver.getMillisecond());
        _cache_update_timer[MINUTE]
                = MINUTE_MILLIS - (long)(_driver.getSecond() * SECOND_MILLIS);
        _cache_update_timer[HOUR]
                = HOUR_MILLIS   - (long)(_driver.getMinute() * MINUTE_MILLIS);
        _cache_update_timer[DAY]
                = DAY_MILLIS    - (long)(_driver.getHour()   * HOUR_MILLIS);
        _cache_timers_set = true;
        /* DEBUG */     Serial.println("complete!");//FIXME: move to debugger
}

// TODO: description
void GPS::_initialize_datetime()
{
        /* DEBUG */     Serial.print("gps: initializing datetime...");//FIXME: move to debugger
        datetime.set_year(_driver.getYear());
        datetime.set_month(_driver.getMonth());
        datetime.set_day(_driver.getDay());
        datetime.set_hour(_driver.getHour());
        datetime.set_minute(_driver.getMinute());
        datetime.set_second(_driver.getSecond());
        /* DEBUG */     Serial.println("complete!");//FIXME: move to debugger
}

// TODO: description
void IRAM_ATTR GPS::_update_second()
{
        static long elapsed_time{_cache_update_timer[SECOND]};
        if (millis() - elapsed_time >= SECOND_MILLIS) {
                /* DEBUG */     Serial.println("updated second");//FIXME: move to debugger
                datetime.set_second(_driver.getSecond());
                elapsed_time = millis();
        }
}

// TODO: description
void IRAM_ATTR GPS::_update_minute()
{
        static long elapsed_time{_cache_update_timer[MINUTE]};
        if (millis() - elapsed_time >= MINUTE_MILLIS) {
                /* DEBUG */     Serial.println("updated minute");//FIXME: move to debugger
                datetime.set_minute(_driver.getMinute());
                elapsed_time = millis();
        }
}

// TODO: description
void IRAM_ATTR GPS::_update_hour()
{
        static long elapsed_time{_cache_update_timer[HOUR]};
        if (millis() - elapsed_time >= HOUR_MILLIS) {
                /* DEBUG */     Serial.println("updated hour");//FIXME: move to debugger
                datetime.set_hour(_driver.getHour());
                elapsed_time = millis();
        }
}

// TODO: description
void IRAM_ATTR GPS::_update_day_month_year()
{
        static long elapsed_time{_cache_update_timer[DAY]};
        if (millis() - elapsed_time >= DAY_MILLIS) {
                datetime.set_day(_driver.getDay());
                datetime.set_month(_driver.getMonth());
                datetime.set_year(_driver.getYear());
                elapsed_time = millis();
        }
}

// TODO: description
void IRAM_ATTR GPS::_update_location()
{
        location.set_location(
                _driver.getLatitude(),
                _driver.getLongitude()
        );
}

/**
 * Reads the GPS vehicle speed.
 **/
void IRAM_ATTR GPS::_update_vehicle_speed()
{
        vehicle_speed = _driver.getGroundSpeed();
}

// TODO: description
void GPS::_start_driver()
{
        _driver.begin();
        _driver.setI2COutput(COM_TYPE_UBX);
        _driver.setNavigationFrequency(NAVIGATION_FREQ);
        _driver.saveConfiguration();
}

// TODO: description
void GPS::_display_seconds_waiting()
{
        static long elapsed_time   {0};
        static int  seconds_waiting{0};

        if (millis() - elapsed_time >= SECOND_MILLIS) {
                /* DEBUG */     Serial.print(".");//FIXME: move to debugger
                elapsed_time = millis();
                seconds_waiting++;
        }

        if (seconds_waiting > 10) {
                /* DEBUG */     Serial.println();//FIXME: move to debugger
                seconds_waiting = 0;
        }
}
