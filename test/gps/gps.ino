#include "gps.h"

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200); // Debugging

        GPS *gps = new GPS;
        gps->satellite_is_connected();
        gps->vehicle_is_moving();
        gps_data data = gps->read();
        Serial.printf("Date: %04d-%02d-%02d\n",
                data.year,
                data.month,
                data.day);
        Serial.printf("Time: %02d-%02d-%02d.%02d\n",
                data.hour,
                data.minute,
                data.second,
                data.millisecond);
        Serial.printf("Location: %0.6lf, %0.6lf\n",
                data.latitude,
                data.longitude);
        Serial.printf("Vehicle Speed: %0.6lf\n",
                data.speed);
        gps->connect_to_satellites();
}

void loop()
{

}