#include "gps.h"

/**
 * To Test:
 * [@] GPS::GPS();
 * [@] GPS::is_connected_to_satellites();
 * [@] GPS::connect_to_satellites();
 * [@] GPS::connect_to_satellites(long timer);
 * [@] GPS::update_cache(year);
 * [@] GPS::update_cache(month);
 * [@] GPS::update_cache(day);
 * [@] GPS::update_cache(hour);
 * [@] GPS::read();
 * [@] GPS::vehicle_state();
 **/

// Test constructor
GPS gps;

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200); // Debugging


        // Test vehicle_state --> unknown
        switch (gps.vehicle_state()) {
        case idle:
                break;
        case moving:
                break;
        case unknown:
                break;
        }

        // Test is_connected_to_satellites()
        while (!gps.is_connected_to_satellites()) {
                // Test connect_to_satellites(long timer)
                gps.connect_to_satellites(10000);  // 10 seconds.
        }

        // Test update_cache(type)
        gps.update_cache(year);
        gps.update_cache(month);
        gps.update_cache(day);
        gps.update_cache(hour);
        gps.update_cache(minute);

        // Test vehicle_state --> idle
        switch (gps.vehicle_state()) {
        case idle:
                break;
        case moving:
                break;
        case unknown:
                break;
        }

        gps_data gps_dat = gps.read();
        Serial.printf("Year:\t%04d\n",          gps_dat.year);
        Serial.printf("Month:\t%02d\n",         gps_dat.month);
        Serial.printf("Day:\t%02d\n",           gps_dat.day);
        Serial.printf("Hour:\t%02d\n",          gps_dat.hour);
        Serial.printf("Minute:\t%02d\n",        gps_dat.minute);
        Serial.printf("Second:\t%02d\n",        gps_dat.second);
        Serial.printf("Millisecond:\t%02d\n",   gps_dat.millisecond);
        Serial.printf("Latitude:\t%0.6lf\n",    gps_dat.latitude);
        Serial.printf("Longitude:\t%0.6lf\n",   gps_dat.longitude);
        Serial.printf("Speed:\t%0.3f\n",        gps_dat.speed);
}

void loop()
{
        gps_data gps_dat = gps.read();
        Serial.printf("Year:\t%04d\n",          gps_dat.year);
        Serial.printf("Month:\t%02d\n",         gps_dat.month);
        Serial.printf("Day:\t%02d\n",           gps_dat.day);
        Serial.printf("Hour:\t%02d\n",          gps_dat.hour);
        Serial.printf("Minute:\t%02d\n",        gps_dat.minute);
        Serial.printf("Second:\t%02d\n",        gps_dat.second);
        Serial.printf("Millisecond:\t%02d\n",   gps_dat.millisecond);
        Serial.printf("Latitude:\t%d\n",        gps_dat.latitude);
        Serial.printf("Longitude:\t%d\n",       gps_dat.longitude);
        Serial.printf("Speed:\t%0.3f\n",        gps_dat.speed);
        delay(1000);
}