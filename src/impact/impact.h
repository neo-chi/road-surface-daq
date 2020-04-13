#pragma once

#include "Arduino.h"
#include "acceleration.h"
#include "loggable.h"
#include "datetime.h"
#include "environment.h"
#include "location.h"

#define IMPACT_NUM_LOGS_MAX ACC_BUF_LEN + 1  // 1 line of impact information,
                                             // plus each line of acceleration
class Impact : public Loggable
{
        public:
                Impact();
                void log();
                bool log_is_full();
                void point_to(DateTime&     datetime);
                void point_to(Location&     location);
                void point_to(Environment&  environment);
                void point_to(Acceleration *acceleration);
                void point_to(int32_t&      vehicle_speed);
        private:
                DateTime     *_datetime     {new DateTime};
                Location     *_location     {new Location};
                Environment  *_environment  {new Environment};
                Acceleration *_acceleration {new Acceleration};
                int32_t      *_vehicle_speed{(int32_t*)malloc(sizeof(int32_t))};
                int           _num_logs     {0};
};
