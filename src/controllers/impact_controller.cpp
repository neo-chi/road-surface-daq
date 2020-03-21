#include "impact_controller.h"

/**
 * Default constructor.
 **/
ImpactController::ImpactController()
{
        Serial.println("Created an impact_controller.");
        Serial.println();
}

/**
 * Returns an impact data structure.
 *
 * @param {gps_data}           gps
 * @param {environmental_data} environment
 * @param {accelerometer_data} acceleration_buffer
 * @param {int}                acceleration_buffer_length
 *
 * @returns {impact_data}      impact date, time, location, environment,
 *                             vehicle speed, and acceleration.
 **/
impact_data ImpactController::create_impact(
        gps_data gps,
        environmental_data environment,
        accelerometer_data *acceleration_buffer,
        int acceleration_buffer_length)
{
        Serial.println("Creating an impact entity.");
        impact_data impact;
        impact.year                             = gps.year;
        impact.month                            = gps.month;
        impact.day                              = gps.day;
        impact.latitude                         = gps.latitude;
        impact.longitude                        = gps.longitude;
        impact.speed                            = gps.speed;
        impact.hour                             = gps.hour;
        impact.minute                           = gps.minute;
        impact.second                           = gps.second;
        impact.millisecond                      = gps.millisecond;
        impact.temperature                      = environment.temperature;
        impact.humidity                         = environment.humidity;
        impact.pressure                         = environment.pressure;
        impact.altitude                         = environment.altitude;
        impact.acceleration_buffer              = acceleration_buffer;
        impact.acceleration_buffer_length       = acceleration_buffer_length;
        Serial.println("Impact entity created!");
        return impact;
}

/**
 * Writes impact content to a file in storage.
 * Directory and file name are predefined.
 * Directory: impact date.
 * File: impact time.
 *
 * @param {Storage}     storage location written to.
 * @param {impact_data} impact information structure.
 **/
void ImpactController::log_impact(Storage storage, impact_data impact)
{
        char *date                       = date_of(impact);
        char *time                       = time_of(impact);
        char *location                   = location_of(impact);
        char *speed                      = speed_of_vehicle_at(impact);
        char *environment                = environment_of(impact);
        char **acceleration_response_set = acceleration_response_of(impact);
        append_to_log(date);
        append_to_log(time);
        append_to_log(location);
        append_to_log(speed);
        append_to_log(environment);

        // Append acceleration array to log buffer.
        for (int i = 0; i < 512; i++) {
                append_to_log(*acceleration_response_set);
                ++acceleration_response_set;
        }

        // Generate file path.
        char *log_file_path = (char *)malloc(16 * sizeof(char));
        sprintf(log_file_path, "/%04d%02d%02d/%02d%02d%02d%02d.imp",
                impact.year,
                impact.month,
                impact.day,
                impact.hour,
                impact.minute,
                impact.second,
                impact.millisecond);

        // reset HEAD and write impact to file.
        log_buffer = log_buffer_ptr_init;  // reset HEAD
        storage.write(log_file_path, log_buffer, log_buffer_length);
}

/**
 * Returns the date string YYYY-MM-DD from gps data.
 *
 * @param {impact_data} impact
 *
 * @returns {char*}     date of impact
 **/
char *ImpactController::date_of(impact_data impact)
{
        char *date = (char *)malloc(32 * sizeof(char));
        sprintf(date, "%04d-%02d-%02d",
                impact.year,
                impact.month,
                impact.day);
        return date;
}

/**
 * Returns the time string HH:MM:SS.ss
 *
 * @param {impact_data} impact
 *
 * @returns {char*}     time of impact
 **/
char *ImpactController::time_of(impact_data impact)
{
        char *time = (char *)malloc(sizeof(char) * 32);
        sprintf(time, "%02d:%02d:%02d.%02d",
                impact.hour,
                impact.minute,
                impact.second,
                impact.millisecond);
        return time;
}

/*
 * Returns the vehicle speed string.
 *
 * @param {impact_data} impact
 *
 * @returns {char*}     speed of vehicle
 */
char *ImpactController::speed_of_vehicle_at(impact_data impact)
{
        char *speed = (char *)malloc(sizeof(char) * 32);
        sprintf(speed, "%0.6lf",
                impact.speed);
        return speed;
}

/**
 * Returns the impact location string.
 *
 * @param {impact_data} impact
 *
 * @returns {char*}     location of impact
 **/
char *ImpactController::location_of(impact_data impact)
{
        char *location = (char *)malloc(sizeof(char) * 32);
        sprintf(location, "%0.6f, %0.6f",
                impact.latitude,
                impact.longitude);
        return location;
}

/**
 * Returns the impact environment string.
 *
 * @param {impact_data} impact
 *
 * @returns {char}      impact environment information
 **/
char *ImpactController::environment_of(impact_data impact)
{
        char *environment = (char *)malloc(sizeof(char) * 32);
        sprintf(environment, "%0.3f, %0.3f, %0.3f, %0.3f",
                impact.temperature,
                impact.humidity,
                impact.pressure,
                impact.altitude);
        return environment;
}

/**
 * Returns the array of acceleration data point strings.
 *
 * @param {impact_data} impact
 *
 * @returns {char**}    acceleration data set
 **/
char **ImpactController::acceleration_response_of(impact_data impact)
{
        const int num_acceleration_points = 512;
        char **acceleration_set   = (char **)malloc(sizeof(char)  * num_acceleration_points * 4);
        char **acceleration_set_o = acceleration_set;  // save initial pointer address

        // populate the acceleration set with points
        for (int i = 0; i < num_acceleration_points; i++) {
                *acceleration_set = (char *)malloc(sizeof(char) * 32);
                sprintf(*acceleration_set, "%0.3f, %0.3f, %0.3f",
                        impact.acceleration_buffer->x,
                        impact.acceleration_buffer->y,
                        impact.acceleration_buffer->z);
                ++acceleration_set;            // increment HEAD
                ++impact.acceleration_buffer;
        }
        acceleration_set = acceleration_set_o; // reset HEAD

        return acceleration_set;
}

/**
 * Add data to the log for file writing.
 *
 * @param {char*} message
 **/
void ImpactController::append_to_log(char *message)
{
        Serial.println("Added to log!");
        *log_buffer = (char *)malloc(32 * sizeof(char));  // allocating space for the new word...
        strcpy(*log_buffer, message);
        ++log_buffer;
        log_buffer_length++;
        Serial.println("Added to log complete!");
}
