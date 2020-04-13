/******************************************************************************
 * @file	accelerometer.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-25
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * The accelerometer class defines the implementation specific behaviours for
 * the accelerometer used in this project. A driver library must be included
 * and constructed in the private member "driver" of this class in order for
 * this class to function properly.
 *
 * This class features:
 *      - Z axis HIGH interrupt
 *      - 800 sample, 3 axis, pre-impact buffer
 *      - 1600 sample, 3 axis, post-impact buffer
 *      - burst reading of pre-impact and post-impact buffers
 *
 * The LIS3DH accelerometer was selected for this design, and the supporting
 * driver library by Adafruit, "Adafruit_LIS3DH" is used to in this
 * initial implementation.
*******************************************************************************/
#pragma once

#include "Arduino.h"
#include "Adafruit_LIS3DH.h"
#include "acceleration.h"

#define PRE_IMP_BUF_LEN         400
#define POST_IMP_BUF_LEN        800
#define ACC_BUF_LEN             PRE_IMP_BUF_LEN + POST_IMP_BUF_LEN
#define ACCELEROMETER_DATARATE  LIS3DH_DATARATE_LOWPOWER_1K6HZ
#define ACCELEROMETER_RANGE     LIS3DH_RANGE_2_G

/**
 * Specifies the types of buffers to read data into.
 *
 * @PRE_IMPACT  the rolling buffer, acceleration data leading up to an impact.
 * @POST_IMPACT  buffer of acceleration data after an impact, detailing an
 *               impact response.
 **/
enum buffer {
        PRE_IMPACT,
        POST_IMPACT
};

class Accelerometer
{
        public:
                Accelerometer();
                void          begin();
                void          read(buffer buffer_to_write = PRE_IMPACT);
                void          unlatch_interrupt();
                volatile bool interrupt_is_latched();
                Acceleration  *acceleration = new Acceleration;
        private:
		volatile bool   __interrupt_has_occured = false;
                Adafruit_LIS3DH __driver;
                void            __set_data_rate();
                void            __set_range();
                void            __enable_z_high_interrupt();
                void            __start_driver();
                void            __write_register_8(int reg, int value);
};
