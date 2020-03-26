/******************************************************************************
 * @file	accelerometer.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-25
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#pragma once

#include "Arduino.h"
#include "accelerometer_data.h"
#include "Adafruit_LIS3DH.h"

#define BUF_LEN 1600  // 1600 samples

class Accelerometer
{
        public:
                Accelerometer();
                accelerometer_data      *read();
                int                     buffer_length();
                void                    unlatch_interrupt();
                volatile bool           interrupt_is_latched();
                bool                    buffer_is_full();
        private:
                Adafruit_LIS3DH         driver;
                accelerometer_data      buffer[BUF_LEN];
                int			buffer_len		= BUF_LEN;
		size_t 			buffer_pointer		= 0;
		volatile bool		interrupt_has_occured	= false;;
};
