#include "impact.h"

Impact::Impact() : Loggable()
{
        // nothing to do here...
}

/**
 * Writes the log data
 * {YYYY-MM-DD HH:MM:SS, latitude, longitude
 * to this object's buffer.
 **/
void Impact::log()
{
        _set_dir(__datetime->get_date());
        _set_filename(__datetime->get_time(), "imp");
        _set_path(_dir, _filename);

        // Logs base data (datetime, lat, lng, ai severity)
        size_t number_of_bytes_written = 0;
        number_of_bytes_written += sprintf(
                _log + number_of_bytes_written,
                "%s,%s,ai_severity=5\n",
                __datetime->to_string(),
                __location->to_string()
        );
        __num_logs++;

        // Logs acceleration for ai_severity calculation
        for (int i = 0; i < ACC_BUF_LEN; i++) {
                number_of_bytes_written += sprintf(
                        _log + number_of_bytes_written,
                        "%0.4f\n",
                        __acceleration->z[i]
                );
                __num_logs++;
        }
        _log_size = number_of_bytes_written;
}

bool Impact::log_is_full()
{
        if (__num_logs > IMPACT_NUM_LOGS_MAX)
                return true;
        else
                return false;
}

void Impact::point_to(DateTime& datetime)
{
        this->__datetime = &datetime;
}

void Impact::point_to(Location& location)
{
        this->__location = &location;
}

void Impact::point_to(Environment& environment)
{
        this->__environment = &environment;
}

void Impact::point_to(int32_t& vehicle_speed)
{
        this->__vehicle_speed = &vehicle_speed;
}

void Impact::point_to(Acceleration *acceleration)
{
        this->__acceleration = acceleration;
}
