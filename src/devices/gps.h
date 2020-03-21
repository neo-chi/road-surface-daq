#pragma once

#include "Arduino.h"
#include "gps_data.h"
#include "gps_cache_enum.h"
#include "gps_vehicle_state_enum.h"
//#include "SparkFun_Ublox_Arduino_Library.h"

class GPS
{
        public:
                GPS();
                gps_data read();
                void connect_to_satellites(long timeout = 0);
                bool is_connected_to_satellites();
                vehicle_state vehicle_state();
                void update_cache(gps_cache type);
        private:
                // SFE_UBLOX_GPS driver

                gps_data data;
                bool cache_is_initialized = false;
                gps_data cache;
};
