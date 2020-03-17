#pragma once

#include "Arduino.h"
#include "gps_data.h"
//#include "SparkFun_Ublox_Arduino_Library.h"

class GPS
{
        public:
                gps_data *read();
                void connect_to_satellites(long timeout = 0);
                bool satellite_is_connected();
                bool vehicle_is_moving();
        private:
                // SFE_UBLOX_GPS driver
                uint16_t year_cache;
                uint8_t month_cache;
                uint8_t day_cache;
                uint8_t hour_cache;
                uint8_t minute_cache;
};