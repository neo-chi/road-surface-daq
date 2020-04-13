#include "impact.h"

// TODO: add description
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
        _set_dir(*_datetime);
        _set_filename(*_datetime, "imp");
        _set_path(_dir, _filename);

        // Logs base data (datetime, lat, lng, ai severity)
        size_t number_of_bytes_written = 0;
        number_of_bytes_written += sprintf(
                _log + number_of_bytes_written,
                "%s,%s,ai_severity=10\n",
                _datetime->to_string(),
                _location->to_string()
        );
        _num_logs++;

        // Logs acceleration for ai_severity calculation
        for (int i = 0; i < ACC_BUF_LEN; i++) {
                number_of_bytes_written += sprintf(
                        _log + number_of_bytes_written,
                        "%0.4f\n",
                        _acceleration->z[i]
                );
                _num_logs++;
        }
        _log_size = number_of_bytes_written;
}

// TODO: add description
bool Impact::log_is_full()
{
        if (_num_logs > IMPACT_NUM_LOGS_MAX)
                return true;
        else
                return false;
}

// TODO: add description
void Impact::point_to(DateTime& datetime)
{
        this->_datetime = &datetime;
}

// TODO: add description
void Impact::point_to(Location& location)
{
        this->_location = &location;
}

// TODO: add description
void Impact::point_to(Environment& environment)
{
        this->_environment = &environment;
}

// TODO: add description
void Impact::point_to(int32_t& vehicle_speed)
{
        this->_vehicle_speed = &vehicle_speed;
}

// TODO: add description
void Impact::point_to(Acceleration *acceleration)
{
        this->_acceleration = acceleration;
}
