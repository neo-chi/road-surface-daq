#include "impact_controller.h"

/**
 * Default constructor.
 **/
ImpactController::ImpactController()
{

}

/**
 * Sets this controller's storage.
 * @param storage
 **/
void ImpactController::attach(Storage *storage)
{
        this->storage = storage;
        Serial.printf("impact_controller: attached storage\n");
}

/**
 * Sets this controller's accelerometer.
 * @param accelerometer
 **/
void ImpactController::attach(Accelerometer *accelerometer)
{
        this->accelerometer = accelerometer;
        Serial.printf("impact_controller: attached accelerometer\n");
}

/**
 * Sets this controller's gps.
 * @param gps
 **/
void ImpactController::attach(GPS *gps)
{
        this->gps = gps;
        Serial.printf("impact_controller: attached gps\n");
}

/**
 * Sets this controller's environmental sensor.
 * @param environmental_sensor
 **/
void ImpactController::attach(EnvironmentalSensor *environmental_sensor)
{
        this->environmental_sensor = environmental_sensor;
        Serial.printf("impact_controller: attached environmental_sensor\n");
}

/**
 * Enables wifi for this controller
 * @param wifi
 **/
void ImpactController::attach(WiFiManager *wifi)
{
        this->wifi = wifi;
        Serial.printf("impact_controller: attached wifi\n");
}

/**
 * Stores gps, environmental sensor, and accelerometer data into
 * local data structure for processing.
 **/
void IRAM_ATTR ImpactController::create_impact()
{
        Serial.print("impact_controller: creating an impact entity...");
        impact.year                = gps->data.year;
        impact.month               = gps->data.month;
        impact.day                 = gps->data.day;
        impact.latitude            = gps->data.latitude;
        impact.longitude           = gps->data.longitude;
        impact.speed               = gps->data.speed;
        impact.hour                = gps->data.hour;
        impact.minute              = gps->data.minute;
        impact.second              = gps->data.second;
        impact.millisecond         = gps->data.millisecond;
        impact.temperature         = environmental_sensor->data.temperature;
        impact.humidity            = environmental_sensor->data.humidity;
        impact.pressure            = environmental_sensor->data.pressure;
        impact.acceleration_buffer = accelerometer->impact;
        Serial.println("complete!");
}

/**
 * Writes impact content to a file in storage.
 * Directory and file name are predefined.
 * Directory: impact date.
 * File: impact time.
 **/
void IRAM_ATTR ImpactController::log_impact()
{
        Serial.println("impact_controller: writing impact log...");
        _log_impact_date();
        _log_impact_time();
        _log_impact_location();
        _log_impact_vehicle_speed();
        _log_impact_environment();
        _log_impact_acceleration();
        _generate_log_directory();
        _generate_log_filename();
        _write_impact_log();
        Serial.println("complete!");
}

/**
 * Stores accelerometer data into local data structure for processing.
 * This method is implemented when there is no GPS satellite connection and
 * therefore, insufficient data is available to generate a complete impact log.
 **/
void IRAM_ATTR ImpactController::log_acceleration()
{
        Serial.println("impact_controller: writing acceleration log...");
        impact.acceleration_buffer = this->accelerometer->impact;
        _log_impact_acceleration();
        _write_acceleration_log();
        Serial.println("complete!");
}

/**
 * TODO: implement this
 **/
void ImpactController::upload_impact(const char *location)
{
        Serial.println("TODO: impact_controller: uploading impact...");
}

void IRAM_ATTR ImpactController::_write_impact_log()
{
        sprintf(path, "%s/%s", log_dir, log_filename);
        Serial.printf("Writing to %s\n", path);
        char *log_HEAD = log;
        storage->mkdir(log_dir);
        storage->write(path, (uint8_t*)log_HEAD, offset);
        _reset_offset();
        memset(log, 0, IMPACT_LOG_SIZE_MAX);  // erases previous log data
}

void IRAM_ATTR ImpactController::_write_acceleration_log()
{
        char *log_HEAD = log;
        storage->write("/acceleration.log", (uint8_t*)log_HEAD, offset);
        _reset_offset();
        memset(log, 0, IMPACT_LOG_SIZE_MAX);  // erases previous log data
}

void IRAM_ATTR ImpactController::_log_impact_date()
{
        Serial.print("impact controller: generating date...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%04d-%02d-%02d,",
                impact.year,
                impact.month,
                impact.day);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_log_impact_time()
{
        Serial.print("impact controller: generating time...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%02d:%02d:%02d.%02d,",
                impact.hour,
                impact.minute,
                impact.second,
                impact.millisecond);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_log_impact_location()
{
        Serial.print("impact controller: generating location...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%0.6f,%0.6f,",
                impact.latitude,
                impact.longitude);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_log_impact_vehicle_speed()
{
        Serial.print("impact controller: generating speed...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%0.6lf,",
                impact.speed);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_log_impact_environment()
{
        Serial.print("impact controller: generating envrionment_data...");
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%0.3f,%0.3f,%0.3f\n",
                impact.temperature,
                impact.humidity,
                impact.pressure);
        _extend_offset(number_of_bytes_written);
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_log_impact_acceleration()
{
        Serial.print("impact controller: generating acceleration...");
        size_t number_of_bytes_written = 0;
        for (size_t i = 0; i < ACC_BUF_LEN; i++) {
                number_of_bytes_written = sprintf(
                        log + offset,
                        "%0.3f,%0.3f,%0.3f\n",
                        impact.acceleration_buffer[i].x,
                        impact.acceleration_buffer[i].y,
                        impact.acceleration_buffer[i].z);
                _extend_offset(number_of_bytes_written);
        }
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_generate_log_directory()
{
        Serial.print("impact controller: generating log directory...");
        sprintf(log_dir, "/%04d%02d%02d",
                impact.year,
                impact.month,
                impact.day);
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_generate_log_filename()
{
        Serial.print("impact controller: generating log filename...");
        sprintf(log_filename, "%02d%02d%02d%02d.imp",
                impact.hour,
                impact.minute,
                impact.second,
                impact.millisecond);
        Serial.println("complete!");
}

void IRAM_ATTR ImpactController::_extend_offset(size_t number_of_bytes)
{
        offset += number_of_bytes;
}

void IRAM_ATTR ImpactController::_reset_offset()
{
        offset = 0;
}
