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
                acceleration_data       impact[ACC_BUF_LEN];
        private:
                const int spi_clk       = 1000000;  // 1MHz
                const int sck_pin       =  16;
                const int mosi_pin      =  4;
                const int miso_pin      =  2;
                const int ss_pin        =  15;

                // Pointer to SPI bus... NOTE: call hspi->begin(sck_pin, mosi_pin, miso_pin, ss_pin) to make this work.
                SPIClass  *hspi                = new SPIClass(HSPI);  // uninitialized pointers SPI objects
                Adafruit_LIS3DH         driver = Adafruit_LIS3DH(ss_pin, hspi);

		volatile bool		interrupt_has_occured = false;
};
