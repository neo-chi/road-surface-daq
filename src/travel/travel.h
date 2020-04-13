#pragma once

#include "Arduino.h"

#include <string.h>

#include "loggable.h"
#include "uploadable.h"
#include "datetime.h"
#include "environment.h"
#include "location.h"

#define TRAVEL_NUM_LOGS_MAX 30
#define TRAVEL_LOG_PERIOD   2000  // 2 seconds

class Travel : public Loggable
{
        public:
                Travel();
                void log();
                bool log_is_full();
                void reset();
                void point_to(DateTime&    datetime);
                void point_to(Location&    location);
                void point_to(Environment& environment);
                void point_to(int32_t&     vehicle_speed);
        private:
                DateTime    *__datetime      = new DateTime;
                Location    *__location      = new Location;
                Environment *__environment   = new Environment;
                int32_t     *__vehicle_speed = (int32_t*)malloc(sizeof(int32_t));
                int         __num_logs       = 0;
};
