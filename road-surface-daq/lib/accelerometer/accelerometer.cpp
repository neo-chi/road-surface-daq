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
 * @note call begin() on this object to enable it.
 *
 * @note to configure this accelerometer, edit:
 * 			/src/devices/accelerometer.cpp
 * 			-> Accelerometer::Accelerometer()
 *
 * @returns configured accelerometer.
 **/
Accelerometer::Accelerometer()
{
        Serial.printf("initializing accelerometer...\n");
        Serial.printf("accelerometer power mode:\tlow-power\n");
        Serial.printf("accelerometer datarate:\t\t1.6KHz\n");
        Serial.printf("accelerometer range:\t\t8G\n");
        Serial.printf("accelerometer initialization complete!");
}

void Accelerometer::begin() {
        /* attempt SPI
                int cs_pin   =  15;
                int mosi_pin =  2;
                int miso_pin =  0;
                int sck_pin  =  4;
                Adafruit_LIS3DH(cs_pin, mosi_pin, miso_pin, sck_pin);
        */
        driver.setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
        driver.setRange(LIS3DH_RANGE_8_G);
        driver.begin();
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
                // fill impact[0 - 799]
                for (size_t i = 0; i < PRE_IMP_BUF_LEN; i++) {
                        driver.read();
                        impact[i].x = driver.x_g;
                        impact[i].y = driver.y_g;
                        impact[i].z = driver.z_g;
                }
                break;
        case POST_IMPACT:
                // fill impact[800 - 2399]
                for (size_t i = PRE_IMP_BUF_LEN; i < ACC_BUF_LEN; i++) {
                        driver.read();
                        impact[i].x = driver.x_g;
                        impact[i].y = driver.y_g;
                        impact[i].z = driver.z_g;
                }
                break;
        default:
                break;
        }
        Serial.printf("complete!\n");
}

/**
 * Reads a single accelerometer value and returns an acceleration structure.
 *
 * @returns acceleration struct
 **/
acceleration_data Accelerometer::read()
{
        driver.read();
        return {driver.x_g, driver.y_g, driver.z_g};
        //this->getEvent(event)
}

/**
 * Allow the accelerometer to trigger interrupts again.
 **/
void Accelerometer::unlatch_interrupt()
{
        Serial.println("acclerometer: reading INT1SRC...\n");
        // TODO: driver.readRegister8(LIS3DH_REG_INT1SRC);  // reading the interrupt source register unlatches the interrupt.
        Serial.printf("Unlactched interrupt!\n");
        Serial.printf("acclerometer: setting interrupt_has_occured = false...");
        interrupt_has_occured = false;
        Serial.printf("complete!");
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
        if (this->interrupt_has_occured)
                return true;
        else
                return false;
}
