#include "gps.h"

/**
 * To Test:
 * [ ] GPS::GPS();
 * [ ] GPS::is_connected_to_satellites();
 * [ ] GPS::connect_to_satellites();
 * [ ] GPS::connect_to_satellites(long timer);
 * [ ] GPS::update_cache(year);
 * [ ] GPS::update_cache(month);
 * [ ] GPS::update_cache(day);
 * [ ] GPS::update_cache(hour);
 * [ ] GPS::read();
 * [ ] GPS::vehicle_state();
 **/

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200); // Debugging

        // Test constructor
        GPS gps;

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
                gps.connect_to_satellites();  // 10 seconds.
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
        Serial.println(gps_dat.year);
        Serial.println(gps_dat.month);
        Serial.println(gps_dat.day);
        Serial.println(gps_dat.hour);
        Serial.println(gps_dat.minute);
        Serial.println(gps_dat.second);
        Serial.println(gps_dat.millisecond);
        Serial.println(gps_dat.latitude);
        Serial.println(gps_dat.longitude);
        Serial.println(gps_dat.speed);
}

void loop()
{

}