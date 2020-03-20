#include "gps.h"

/**
 * GPS constructor
 *
 * @returns GPS
 */
GPS::GPS()
{
        Serial.println("Created a gps.");
}

/**
 * Read GPS data.
 *
 * @returns *gps_data
 */
gps_data GPS::read()
{
        this->data.year = 2020;
        this->data.month = 1;
        this->data.day = 2;
        this->data.hour = 3;
        this->data.minute = 4;
        this->data.second = 5;
        this->data.millisecond = 6;
        this->data.latitude = 7;
        this->data.longitude = 8;
        this->data.speed = 9;
        return data;
}

/**
 * Attempt to get 3 satellite connections. Optional timeout timer.
 */
void GPS::connect_to_satellites(long timeout)
{
        if (timeout == 0) {
                // attempt to connect forever
                long elapsed_time = 0;
                uint8_t seconds_waiting = 0;
                const int MAX_WAIT_SECONDS = 10;
                Serial.print("Waitng until satellite connection is received");
                while (!(this->is_connected_to_satellites())) {
                        if (seconds_waiting > MAX_WAIT_SECONDS) {
                                seconds_waiting = 0;
                                Serial.println();
                        }
                        if (millis() - elapsed_time > 1000) {
                                Serial.print(".");
                                elapsed_time = millis();
                                seconds_waiting++;
                        }

                }
        } else {
                long elapsed_time = 0;
                uint8_t seconds_waiting = 0;
                Serial.printf("Waiting %d milliseconds until satellite connection is received.");
                while (millis() - elapsed_time < timeout) {
                        if (seconds_waiting >= 3)
                                Serial.printf("\b\b\b");
                        if (millis() - elapsed_time > 1000) {
                                Serial.print(".");
                                elapsed_time = millis();
                                seconds_waiting++;
                        }
                }
        }
}

/**
 * Check if GPS is connected to at least 3 satellites.
 *
 * @returns boolean
 */
bool GPS::is_connected_to_satellites()
{
        // TODO [ ] GPS::is_connected_to_satellites()
        return false;
}

/**
 * Check if the vehicle is moving at more than 1000 mm/s.
 *
 * @returns boolean
 */
bool GPS::vehicle_is_moving()
{
        // TODO  [ ]  GPS::vehicles_is_moving()kg
        Serial.print("Checking vehicle movement state... ");
        Serial.println("Vehicle is idle!");
        return false;
}
