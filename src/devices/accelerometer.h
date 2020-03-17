#pragma once

#include "Arduino.h"
#include "accelerometer_data.h"
#include "LIS3DH.h"

class Accelerometer
{
        public:
                Accelerometer();
                accelerometer_data *read();
                int buffer_size();
                void unlatch_interrupt();
                bool interrupt_is_latched();
                bool buffer_is_full();
        private:
                const LIS3DH driver;
                accelerometer_data buffer[512];
                const int buffer_size = 512;
};
