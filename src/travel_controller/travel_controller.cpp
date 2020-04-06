#include "travel_controller.h"

/**
 * Default constructor.
 **/
TravelController::TravelController()
{
        Serial.println("Created a travel controller.");
}

/**
 * Sets this controller's storage.
 **/
void TravelController::attach(Storage *storage)
{
        this->storage = storage;
        Serial.printf("travel_controller: attached storage\n");
}

/**
 * Sets this controllers gps.
 **/
void TravelController::attach(GPS *gps)
{
        this->gps = gps;
        Serial.printf("travel_controller: attached gps\n");
}

/**
 * Sets this controller's environmental sensor.
 **/
void TravelController::attach(EnvironmentalSensor *environmental_sensor)
{
        this->environmental_sensor = environmental_sensor;
        Serial.printf("travel_controller: attached environmental_sensor\n");
}

/**
 * Enables wifi for this controller.
 **/
void TravelController::attach(WiFiManager *wifi) {
        this->wifi = wifi;
        Serial.printf("travel_controller: attached wifi\n");
}

/**
 * Generate a travel entity for processing.
 **/
void TravelController::create_travel()
{
        Serial.print("travel_controller: creating travel entity...");
        travel.year        = gps->data.year;
        travel.month       = gps->data.month;
        travel.day         = gps->data.day;
        travel.hour        = gps->data.hour;
        travel.minute      = gps->data.minute;
        travel.second      = gps->data.second;
        travel.speed       = gps->data.speed;
        travel.temperature = environmental_sensor->data.temperature;
        travel.humidity    = environmental_sensor->data.humidity;
        travel.pressure    = environmental_sensor->data.pressure;
        travel_buffer[number_of_travel_logs] = travel;
        number_of_travel_logs++;
        Serial.println("complete!");
}

/**
 * Writes a this controller's travel buffer to temporary storage.
 *
 * Travel logs are must be stored temporarily until the device has access
 * to uploading.
 **/
void TravelController::log_travel()
{
        Serial.println("travel_controller: writing travel log...");
        for (int i = 0; i < number_of_travel_logs; i++) {
                _log_travel_date(i);
                _log_travel_time(i);
                _log_travel_location(i);
                _log_travel_vehicle_speed(i);
                _log_travel_environment(i);
        }
        _generate_log_directory();
        _generate_log_filename();
        _write_travel_log();
        Serial.println("complete!");
}

/**
 * Uploads a travel log file to the specified php upload script.
 *
 * @param location URL of travel_upload.php script.
 **/
void TravelController::upload_travel(const char *location)
{
        static const long try_for_thirty_seconds = 30000;
        wifi->connect(try_for_thirty_seconds);
        if (wifi->is_connected()) {
                // TODO: loop while file has content...
                HTTPClient http;
                http.begin(location);
                http.addHeader("Content-Type", "url-encoded-form");
                const int http_response_code = http.POST(""); // TODO: travel data goes here.
                if (http_response_code > 0) {
                        Serial.printf("http response code: %d;", http_response_code);
                        Serial.println(http.getString());
                } else {
                        Serial.printf("http post ERROR: %d\n", http_response_code);
                }
                http.end();
                // TODO: end loop
        }
}

/**
 * Returns true if the travel buffer is ready to be written to a log file.
 *
 * @returns bool
 **/
bool TravelController::buffer_is_full()
{
        if (number_of_travel_logs >= TRAVEL_NUMBER_OF_LOGS_MAX)
                return true;
        else
                return false;
}

void TravelController::_write_travel_log()
{
        sprintf(path, "%s/%s", log_dir, log_filename);
        Serial.printf("Writing to %s\n", path);
        char *log_HEAD = log; // Pointer to the first logged data point.
        storage->mkdir(log_dir);
        storage->write(path, (uint8_t*)log_HEAD, offset);
        _reset_offset();
        number_of_travel_logs = 0;
        memset(log, 0, TRAVEL_LOG_SIZE_MAX);
}

void TravelController::_log_travel_date(int travel_buffer_index)
{
        Serial.print("travel controller: generating date...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%04d-%02d-%02d,",
                travel_buffer[travel_buffer_index].year,
                travel_buffer[travel_buffer_index].month,
                travel_buffer[travel_buffer_index].day);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void TravelController::_log_travel_time(int travel_buffer_index)
{
        Serial.print("travel controller: generating time...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%02d:%02d:%02d,",
                travel_buffer[travel_buffer_index].hour,
                travel_buffer[travel_buffer_index].minute,
                travel_buffer[travel_buffer_index].second);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void TravelController::_log_travel_location(int travel_buffer_index)
{
        Serial.print("travel controller: generating location...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%0.6f,%0.6f,",
                travel_buffer[travel_buffer_index].latitude,
                travel_buffer[travel_buffer_index].longitude);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void TravelController::_log_travel_vehicle_speed(int travel_buffer_index)
{
        Serial.print("travel controller: generating speed...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%0.6lf,",
                travel_buffer[travel_buffer_index].speed);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void TravelController::_log_travel_environment(int travel_buffer_index)
{
        Serial.print("travel controller: generating envrionment_data...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%0.3f,%0.3f,%0.3f\n",
                travel_buffer[travel_buffer_index].temperature,
                travel_buffer[travel_buffer_index].humidity,
                travel_buffer[travel_buffer_index].pressure);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void TravelController::_generate_log_directory()
{
        Serial.print("travel controller: generating log directory...");
        sprintf(log_dir, "/%04d%02d%02d",
                travel_buffer[0].year,
                travel_buffer[0].month,
                travel_buffer[0].day);
        Serial.println("complete!");
}

void TravelController::_generate_log_filename()
{
        Serial.print("travel controller: generating log filename...");
        sprintf(log_filename, "%02d%02d%02d.trv",
                travel_buffer[0].hour,
                travel_buffer[0].minute,
                travel_buffer[0].second);
        Serial.println("complete!");
}

void TravelController::_reset_offset()
{
        offset = 0;
}

void TravelController::_extend_offset(size_t number_of_bytes)
{
        offset += number_of_bytes;
}

#pragma endregion HELPER_FUNCTIONS
