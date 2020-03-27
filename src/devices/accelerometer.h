/******************************************************************************
 * @file	accelerometer.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-25
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#pragma once

#include "Arduino.h"
#include "Adafruit_LIS3DH.h"

#define PRE_IMP_BUF_LEN  800
#define POST_IMP_BUF_LEN 1600
#define ACC_BUF_LEN      PRE_IMP_BUF_LEN + POST_IMP_BUF_LEN

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
 */
struct accelerometer_data {
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
                accelerometer_data      read();
                void                    unlatch_interrupt();
                volatile bool           interrupt_is_latched();
                accelerometer_data      pre_impact[PRE_IMP_BUF_LEN];
                accelerometer_data      post_impact[POST_IMP_BUF_LEN];
        private:
                Adafruit_LIS3DH         *driver;
		volatile bool		interrupt_has_occured = false;
};
