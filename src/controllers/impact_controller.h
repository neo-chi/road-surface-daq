#pragma once

#include "Arduino.h"

#include "accelerometer_data.h"
#include "environmental_data.h"
#include "gps_data.h"
#include "impact.h"
//#include "storage.h"

class ImpactController
{
        public:
                ImpactController();
                impact_data create_impact(gps_data *gps,
                                          environmental_data *environment,
                                          accelerometer_data *acceleration_buffer);
                // TODO: void log_impact(Storage storage, impact_data *impact);
                // TODO: void upload_impact(String location);
        private:
};
