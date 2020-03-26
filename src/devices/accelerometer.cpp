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
        Serial.printf("initializing accelerometer...\n");
	Serial.printf("accelerometer power mode:\tlow-power\n");
	Serial.printf("accelerometer datarate:\t1.6 KHz\n");
	Serial.printf("accelerometer range:\t8 G\n");
	driver.setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
	driver.setRange(LIS3DH_RANGE_8_G);
	driver.begin(LIS3DH_DEFAULT_ADDRESS);
	Serial.printf("accelerometer initialization complete!");
}

/**
 * Returns a buffer of x, y, z acceleration data.
 *
 * @returns accelerometer_data
 **/
accelerometer_data *Accelerometer::read()
{
        Serial.printf("Reading accelerometer...");
        for (int i = 0; i < BUF_LEN; i++) {
		driver.read();
                buffer[i].x = driver.x_g;
                buffer[i].y = driver.y_g;
                buffer[i].z = driver.z_g;
        }
        Serial.print("Complete!\n");
        return buffer;
}

/**
 * Returns the size of the acceleration buffer.
 *
 * @return int acceleration buffer size.
 **/
int  Accelerometer::buffer_length()
{
	return buffer_len;
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

/**
 * Returns true if the acceleration buffer is full.
 *
 * @returns bool
 **/
bool Accelerometer::buffer_is_full()
{
	Serial.printf("Accelerometer buffer is full!");
	return true;
}
