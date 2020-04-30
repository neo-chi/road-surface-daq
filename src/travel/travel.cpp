/*******************************************************************************
 * @file	travel.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

#include "travel.h"

Travel::Travel() : Loggable()
{
        // nothing to do here...
}

void Travel::log()
{
        if (!log_is_full()) {
                size_t number_of_bytes_written = 0;
                number_of_bytes_written += sprintf(
                        _log + _log_size,
                        "%s,%s,ai_severity=0\n",
                        _datetime->to_string(),
                        _location->to_string()
                );
                _log_size += number_of_bytes_written;
                _num_logs++;
        }
        if (log_is_full()) {
                _set_dir(*_datetime);
                _set_filename(*_datetime, "trv");
                _set_path(_dir, _filename);
        }
        /* DEBUG */     Serial.printf(
        /* DEBUG */        "%s,%s,ai_severity=0\n",
        /* DEBUG */        _datetime->to_string(),
        /* DEBUG */        _location->to_string()
        /* DEBUG */     );
}

bool Travel::log_is_full()
{
        if (_num_logs >= TRAVEL_NUM_LOGS_MAX)
                return true;
        else
                return false;
}

/**
 * Clears the loggable item's log, directory, filename, path, and resets the size to 0.
 *
 * @note call this method after writing this item's log file.
 **/
void Travel::reset()
{
        Loggable::reset();
        _num_logs = 0;
}

void Travel::point_to(DateTime& datetime)
{
        this->_datetime = &datetime;
}

void Travel::point_to(Location& location)
{
        this->_location = &location;
}

void Travel::point_to(Environment& environment)
{
        this->_environment = &environment;
}

void Travel::point_to(int32_t& vehicle_speed)
{
        this->_vehicle_speed = &vehicle_speed;
}
