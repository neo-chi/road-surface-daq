#include "impact_controller.h"

/**
 * Default constructor.
 **/
ImpactController::ImpactController()
{
}

ImpactController::ImpactController(Storage *storage, Accelerometer *accelerometer, GPS *gps, EnvironmentalSensor *environmental_sensor)
{
        Serial.printf("Initializing impact controller...\n");

        this->storage = storage;
        Serial.printf("impact_controller: attached storage\n");

        this->accelerometer = accelerometer;
        Serial.printf("impact_controller: attached accelerometer\n");

        this->gps = gps;
        Serial.printf("impact_controller: attached gps\n");

        this->environmental_sensor = environmental_sensor;
        Serial.printf("impact_controller: attached environmental_sensor\n");

        Serial.printf("complete!");

}

void ImpactController::attach(Storage *storage)
{
        this->storage = storage;
}
void ImpactController::attach(Accelerometer *accelerometer)
{
        this->accelerometer = accelerometer;
}

void ImpactController::attach(GPS *gps)
{
        this->gps = gps;
}

void ImpactController::attach(EnvironmentalSensor *environmental_sensor)
{
        this->environmental_sensor = environmental_sensor;
}

/**
 * Generates an impact data structure.
 *
 * @param {gps_data}           gps
 * @param {environmental_data} environment
 * @param {accelerometer_data} acceleration_buffer
 **/
void ImpactController::create_impact()
{
        Serial.println("Creating an impact entity.");
        gps_data _gps_data = this->gps->read();
        acceleration_data *_acceleration = this->accelerometer->impact;
        //environmental_data environment = this->environmental_sensor->read();
        environmental_data environment = {10.1, 20.2, 30.3};
        impact.year                             = _gps_data.year;
        impact.month                            = _gps_data.month;
        impact.day                              = _gps_data.day;
        impact.latitude                         = _gps_data.latitude;
        impact.longitude                        = _gps_data.longitude;
        impact.speed                            = _gps_data.speed;
        impact.hour                             = _gps_data.hour;
        impact.minute                           = _gps_data.minute;
        impact.second                           = _gps_data.second;
        impact.millisecond                      = _gps_data.millisecond;
        impact.temperature                      = environment.temperature;
        impact.humidity                         = environment.humidity;
        impact.pressure                         = environment.pressure;
        impact.acceleration_buffer              = _acceleration;
        Serial.println("Impact entity created!");
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
void ImpactController::log_impact()
{
        // FILE FORMAT
        // date
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%04d-%02d-%02d",
                impact.year,
                impact.month,
                impact.day);
        extend_offset(number_of_bytes_written);
        // time
        number_of_bytes_written = sprintf(log + offset, "%02d:%02d:%02d.%02d",
                impact.hour,
                impact.minute,
                impact.second,
                impact.millisecond);
        extend_offset(number_of_bytes_written);
        // location
        number_of_bytes_written = sprintf(log + offset, "%0.6f, %0.6f",
                impact.latitude,
                impact.longitude);
        extend_offset(number_of_bytes_written);
        // speed
        number_of_bytes_written = sprintf(log + offset, "%0.6lf",
                impact.speed);
        extend_offset(number_of_bytes_written);
        // environment
        number_of_bytes_written = sprintf(log + offset, "%0.3f, %0.3f, %0.3f, %0.3f",
                impact.temperature,
                impact.humidity,
                impact.pressure);
        extend_offset(number_of_bytes_written);
        // acceleration_n
        // acceleration_n + 1
        // ...
        for (size_t i = 0; i < ACC_BUF_LEN; i++) {
                number_of_bytes_written = sprintf(           // --> CORRUPT HEAP ERROR
                        log + offset,
                        "%0.3f,%0.3f,%0.3f\n",
                        impact.acceleration_buffer[i].x,
                        impact.acceleration_buffer[i].y,
                        impact.acceleration_buffer[i].z);
                extend_offset(number_of_bytes_written);
        }
        // EOF

        sprintf(log_dir, "/%04d%02d%02d",
                impact.year,
                impact.month,
                impact.day);

        sprintf(log_filename, "%02d%02d%02d%02d.imp",
                impact.hour,
                impact.minute,
                impact.second,
                impact.millisecond);

        sprintf(path, "%s/%s", log_dir, log_filename);
        Serial.printf("Writing to %s\n", path);

        Serial.printf(log);
        //storage.write(path, log);

        reset_offset();
}

/**
 * Add data to the log for file writing.
 *
 * @param {char*} message
 **/
void ImpactController::append_to_log(char *message)
{
        size_t number_of_bytes_written = 0;
        number_of_bytes_written = sprintf(log + offset, "%s", message);
        extend_offset(number_of_bytes_written);
}

void ImpactController::reset_offset()
{
        offset = 0;
}

void ImpactController::extend_offset(size_t number_of_bytes)
{
        offset += number_of_bytes;
}
