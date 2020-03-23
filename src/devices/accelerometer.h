#pragma once

#include "Arduino.h"
#include "accelerometer_data.h"
#include "LIS3DH.h"

#define BUF_LEN 32

class Accelerometer
{
        public:
                Accelerometer();
                accelerometer_data      *read();
                int                     size_buffer();
                void                    unlatch_interrupt();
                volatile bool           interrupt_is_latched();
                bool                    buffer_is_full();
        private:
                LIS3DH            	driver;
                accelerometer_data      buffer[BUF_LEN];
                const int               buffer_size = BUF_LEN;
		size_t 			buffer_ptr = 0;
};
