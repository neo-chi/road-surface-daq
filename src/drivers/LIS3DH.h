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

#define TEMP_CFG_REG_CONFIGURATION  0x80
#define CTRL_REG1_CONFIGURATION     0x97
#define CTRL_REG2_CONFIGURATION     0x00
#define CTRL_REG3_CONFIGURATION     0x40
#define CTRL_REG4_CONFIGURATION     0x08
#define CTRL_REG5_CONFIGURATION     0x08
#define CTRL_REG6_CONFIGURATION     0x00
#define STATUS_REG_CONFIGURATION    0x00
#define FIFO_CTRL_REG_CONFIGURATION 0x00
#define FIFO_SRC_REG_CONFIGURATION  0x00
#define INT1_CFG_CONFIGURATION      0x20
#define INT1_SRC_CONFIGURATION      0x00
#define INT1_THS_CONFIGURATION      0xFF
#define INT1_DURATION_CONFIGURATION 0x00
#define CLICK_CFG_CONFIGURATION     0x00
#define CLICK_SRC_CONFIGURATION     0x00
#define CLICK_THS_CONFIGURATION     0x00
#define TIME_LIMIT_CONFIGURATION    0x00
#define TIME_LATENCY_CONFIGURATION  0x00
#define TIME_WINDOW_CONFIGURATION   0x00

class LIS3DH
{
    public:
        LIS3DH();
		uint8_t configurationRead(const uint8_t reg);
		void configurationWrite(const uint8_t reg, const uint8_t configuration);
		void read_int16();
		//void read_float();
		void read_float(float *x_buf, float *y_buf, float *z_buf, size_t len);

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
