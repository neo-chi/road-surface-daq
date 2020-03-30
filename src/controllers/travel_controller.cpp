#include "travel_controller.h"
/**
 * Default constructor.
 **/
TravelController::TravelController()
{
        Serial.println("Created a travel controller.");
}

/**
 * Returns a travel data entity.
 *
 * @param gps_data
 * @param environmental_data
 *
 * @returns travel_data
 **/
travel_data TravelController::create_travel(gps_data gps,
                                            environmental_data environment)
{
        Serial.print("Creating travel entity...");
        travel_data travel;
        travel.year             = gps.year;
        travel.month            = gps.month;
        travel.day              = gps.day;
        travel.hour             = gps.hour;
        travel.minute           = gps.minute;
        travel.second           = gps.second;
        travel.millisecond      = gps.millisecond;
        travel.speed            = gps.speed;
        travel.temperature      = environment.temperature;
        travel.humidity         = environment.humidity;
        travel.pressure         = environment.pressure;
        travel.altitude         = environment.altitude;
        append_to_log_buffer(travel);
        increment_log_buffer_index();
        Serial.println("Complete!");
        return travel;
}

/**
 * Writes a this controller's travel buffer to temporary storage.
 *
 * Travel logs are must be stored temporarily until the device has access
 * to uploading.
 *
 * @param storage: temporary storage data is written to.
 **/
void TravelController::log_travel(Storage storage)
{
        Serial.print("Logging travel...");
        reset_log_buffer_head();
        for (int i = 0; i < log_buffer_length; i++) {
                storage.write("/test_dir/HHMMSS.trv", *log_buffer);
        }
        Serial.println("Complete!");
}

/**
 * Uploads a travel log file to the specified php upload script.
 *
 * @param location URL of travel_upload.php script.
 **/
void TravelController::upload_travel(String location)
{
        Serial.println("TODO: TravelController::upload_travel");
}

/**
 * Returns true if the travel buffer is ready to be written to a log file.
 *
 * @returns bool
 **/
bool TravelController::buffer_is_full()
{
        if (log_buffer_index > 511)
                return true;
        else
                return false;
}

/**
 *  Helper function.
 **/
char *date_of(travel_data travel)
{
        char *date = (char*)malloc(32 * sizeof(char));
        sprintf(date, "%04d-%02d-%02d",
                travel.year,
                travel.month,
                travel.day);
}

/**
 *  Helper function.
 **/
char *time_of(travel_data travel)
{
        char *time = (char*)malloc(32 * sizeof(char));
        sprintf(time, "%02d-%02d-%02d",
                travel.hour,
                travel.minute,
                travel.second);
}

/**
 *  Helper function.
 **/
char *speed_of(travel_data travel)
{
        char *speed = (char*)malloc(32 * sizeof(char));
        sprintf(speed, "%0.3lf",
                travel.speed);
}

/**
 *  Helper function.
 **/
char *location_of(travel_data travel)
{
        char *location = (char*)malloc(32 * sizeof(char));
        sprintf(location, "%0.6lf, %0.6lf",
                travel.latitude,
                travel.longitude);
}

/**
 *  Helper function.
 **/
char *environment_of(travel_data travel)
{
        char *environment = (char*)malloc(32 * sizeof(char));
        sprintf(environment, "%0.3lf, %0.3lf, %0.3lf, %0.3lf",
                travel.temperature,
                travel.humidity,
                travel.pressure,
                travel.altitude);
}

/**
 *  Helper function.
 **/
void TravelController::append_to_log_buffer(travel_data travel)
{
        *log_buffer = (char *)malloc(32 * sizeof(char));
        char *date              = date_of(travel);
        char *time              = time_of(travel);
        char *speed             = speed_of(travel);
        char *location          = location_of(travel);
        char *environment       = environment_of(travel);
        sprintf(*log_buffer, "%s, %s, %s, %s",
                date,
                time_of(travel),
                speed_of(travel),
                location_of(travel),
                environment_of(travel));
        free(date);
        free(time);
        free(speed);
        free(location);
        free(environment);
}

/**
 *  Helper function.
 **/
void TravelController::reset_log_buffer_head()
{
        log_buffer_index = 0;
}

/**
 *  Helper function.
 **/
void TravelController::increment_log_buffer_index()
{
        log_buffer_index++;
}
