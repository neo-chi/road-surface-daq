/*******************************************************************************
 * @file	accelerometer.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-25
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#include "accelerometer.h"

/**
 * Default constructor.
 *
 * @note to configure this accelerometer, edit:
 * 			/src/devices/accelerometer.cpp
 * 			-> Accelerometer::Accelerometer()
 *
 * @returns configured accelerometer.
 **/
Accelerometer::Accelerometer()
{
}

void Accelerometer::begin()
{
        Serial.printf("initializing accelerometer...\n");
        Serial.printf("accelerometer power mode:\tlow-power\n");
        Serial.printf("accelerometer datarate:\t\t1.6 KHz\n");
        Serial.printf("accelerometer range:\t\t8 G\n");
        this->driver = new Adafruit_LIS3DH;
        this->driver->setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
        this->driver->setRange(LIS3DH_RANGE_8_G);
        this->driver->begin(LIS3DH_DEFAULT_ADDRESS);
        Serial.printf("accelerometer initialization complete!");
}

/**
 * Reads data into the specified buffer, given the context.
 *
 * @note PRE_IMPACT should be passed during regular operation.
 * @note POST_IMPACT should be passed on interrupt.
 *
 * @param buffer_to_write
 **/
void Accelerometer::read(acc_buffer buffer_to_write)
{
        Serial.printf("Reading accelerometer...");
        switch (buffer_to_write) {
        case PRE_IMPACT:
                for (size_t i = 0; i < PRE_IMP_BUF_LEN; i++) {
                        this->driver->read();
                        pre_impact[i].x = this->driver->x_g;
                        pre_impact[i].y = this->driver->y_g;
                        pre_impact[i].z = this->driver->z_g;
                }
                break;
        case POST_IMPACT:
                for (size_t i = 0; i < POST_IMP_BUF_LEN; i++) {
                        this->driver->read();
                        post_impact[i].x = this->driver->x_g;
                        post_impact[i].y = this->driver->y_g;
                        post_impact[i].z = this->driver->z_g;
                }
                break;
        default:
                break;
        }
}

accelerometer_data Accelerometer::read()
{
        this->driver->read();
        return accelerometer_data{driver->x_g, driver->y_g, driver->z_g};
}

/**
 * Allow the accelerometer to trigger interrupts again.
 **/
void Accelerometer::unlatch_interrupt()
{
        // [ ] Implement this!
        Serial.printf("Unlactched interrupt!\n");
}

/**
 * Returns true if the accelerometer triggered an interrupt.
 *
 * @note return value is volatile because it can be modified at any point.
 *
 * @returns volatile bool
 **/
volatile bool Accelerometer::interrupt_is_latched()
{
        // [ ] Implement this!
        Serial.printf("Accelerometer buffer is latched.");
        return true;
}
