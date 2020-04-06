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
enum acc_buffer {
        PRE_IMPACT,
        POST_IMPACT
};

/**
 * Aggregates accelerometer data.
 *
 * @x acceleration
 * @y acceleration
 * @z acceleration
 **/
struct acceleration_data {
        float x;
        float y;
        float z;
};

class Accelerometer
{
        public:
                Accelerometer();
                void                    begin();
                void                    read(acc_buffer buffer_to_write);
                acceleration_data       read();
                void                    unlatch_interrupt();
                volatile bool           interrupt_is_latched();
		volatile bool		interrupt_has_occured = false;
                acceleration_data       impact[ACC_BUF_LEN];
        private:
                Adafruit_LIS3DH         driver;
                void                    _set_data_rate();
                void                    _set_range();
                void                    _enable_z_high_interrupt();
                void                    _start_driver();
                void                    _write_register_8(int reg, int value);
};
