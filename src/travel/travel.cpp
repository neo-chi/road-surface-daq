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
                        __datetime->to_string(),
                        __location->to_string()
                );
                _log_size += number_of_bytes_written;
                __num_logs++;
        }
        if (log_is_full()) {
                _set_dir(*__datetime);
                _set_filename(*__datetime, ".trv");
                _set_path(_dir, _filename);
        }
        /* DEBUG */     Serial.printf(
        /* DEBUG */        "%s,%s,ai_severity=0\n",
        /* DEBUG */        __datetime->to_string(),
        /* DEBUG */        __location->to_string()
        /* DEBUG */     );
}

bool Travel::log_is_full()
{
        if (__num_logs >= TRAVEL_NUM_LOGS_MAX)
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
        __num_logs = 0;
}

void Travel::point_to(DateTime& datetime)
{
        this->__datetime = &datetime;
}

void Travel::point_to(Location& location)
{
        this->__location = &location;
}

void Travel::point_to(Environment& environment)
{
        this->__environment = &environment;
}

void Travel::point_to(int32_t& vehicle_speed)
{
        this->__vehicle_speed = &vehicle_speed;
}
