#pragma once

#include "Arduino.h"
#include "entities/loggable.h"
#include "entities/uploadable.h"
#include "entities/date.h"
#include "entities/time.h"
#include "entities/location.h"
#include "entities/environment.h"

/*
 * Travel - records healthy road information.
 *
 * @log(): returns a String for file writing.
 * @location_header(): returns a String detailing the upload location.
 * @post(): returns a String of HTTP POST data.
 *
 * @gps_is_connected: boolean true if gps had sattelite connection.
 * @DAQ_ID: unique data acquisition device identity.
 * @date: date of data collection.
 * @time: time of data collection.
 * @location: google maps latitude and longitude.
 * @speed: vehicle speed in mm/s.
 */
class Travel : Loggable, Uploadable
{
        public:
                String log();
                String location_header();
                String post();
        private:
                const bool gps_is_connected;
                const int DAQ_ID;
                date date;
                location location;
                time time;
                float speed;
};
