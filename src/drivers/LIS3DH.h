/*
 * Arduino ESP32 support for LIS3DH accelerometer.
 * 
 * @author Reece Chimento
 */

#ifndef LIS3DH_h
#define LIS3DH_h

#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////
// I2C Slave Address
////////////////////////////////////////////////////////////////////////////////

#define LIS3DH_SLAVE_ADDRESS 0x18 // Arduino uses 7 byte slave address.

////////////////////////////////////////////////////////////////////////////////
// Register Mapping
////////////////////////////////////////////////////////////////////////////////

#define TEMP_CFG_REG  0x1F
#define CTRL_REG1     0x20
#define CTRL_REG2     0x21
#define CTRL_REG3     0x22
#define CTRL_REG4     0x23
#define CTRL_REG5     0x24
#define CTRL_REG6     0x25
#define STATUS_REG    0x27
#define OUT_X_L       0x28
#define OUT_X_H       0x29
#define OUT_Y_L       0x2A
#define OUT_Y_H       0x2B
#define OUT_Z_L       0x2C
#define OUT_Z_H       0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG  0x2F
#define INT1_CFG      0x30
#define INT1_SRC      0x31
#define INT1_THS      0x32
#define INT1_DURATION 0x33
#define CLICK_CFG     0x38
#define CLICK_SRC     0x39
#define CLICK_THS     0x3A
#define TIME_LIMIT    0x3B
#define TIME_LATENCY  0x3C
#define TIME_WINDOW   0x3D

enum fifo_mode
{
	STREAM,
	STREAM_TO_FIFO
};

class LIS3DH
{
    public:
        LIS3DH();
		uint8_t configurationRead(const uint8_t reg);
		void configurationWrite(const uint8_t reg, const uint8_t configuration);
		void read();

		int16_t x;
		int16_t y;
		int16_t z;

		float x_g;
		float y_g;
		float z_g;
    private:
		float readOutput(const uint8_t OUT_axis_L);
};

#endif
