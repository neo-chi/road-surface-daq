/*!
 * Arduino ESP32 support for LIS3H accelerometer.
 * 
 * @author Reece Chimento
 */

#include "LIS3DH.h"
#include "Wire.h"

/*!
 * @brief Constructor
 */
LIS3DH::LIS3DH()
{
	Wire.begin();
	Serial.println("(II) LIS3DH initialized on I2C bus.");
}

/*!
 * @brief Read existing sensor configuration register content.
 *
 * @param uint8_t reg  register to read contents of.
 *
 * @return register configuration content.
 */
uint8_t LIS3DH::configurationRead(const uint8_t reg)
{
	// Set register pointer to {reg} to prepare for reading.
	Wire.beginTransmission(LIS3DH_SLAVE_ADDRESS); 
	Wire.write(reg);
	Wire.endTransmission();

	// Allow LIS3DH response time.
	delayMicroseconds(50);

	// Request a single byte from {reg}.
	const int NUM_BYTES = 1;
	Wire.requestFrom(LIS3DH_SLAVE_ADDRESS, NUM_BYTES);

	// Allow LIS3DH response time.
	delayMicroseconds(50);

	// Read the byte and store in {regContent}.
	uint8_t regContent;
	if (Wire.available()) {
		regContent = Wire.read();
	}

	return regContent;
}
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Update sensor configuration register.
 *
 * @param uint8_t reg  register to be configured.
 * @param uint8_t configuration  new register configuration.
 *
 * @return  new register configuration.
 */
void LIS3DH::configurationWrite(const uint8_t reg, const uint8_t configuration)
{
	// Move register pointer to {reg}.
	Wire.beginTransmission(LIS3DH_SLAVE_ADDRESS);
	Wire.write(reg);
	Wire.write(configuration);
	Wire.endTransmission();
	
	// Allow LIS3DH response time.
	delayMicroseconds(50);
}

/*!
 * @brief Read the x, y, and z acceleration registers.
 */
void LIS3DH::read()
{
	Wire.beginTransmission(LIS3DH_SLAVE_ADDRESS);
	Wire.write(OUT_X_L | 0x80); // 0x80 -> autoincrement
	Wire.endTransmission();

	Wire.requestFrom(LIS3DH_SLAVE_ADDRESS, 6);

	x = Wire.read();
	x |= ((uint16_t)Wire.read()) << 8;

	y = Wire.read();
	y |= ((uint16_t)Wire.read()) << 8;

	z = Wire.read();
	z |= ((uint16_t)Wire.read()) << 8;

	x_g = (float)x / 16380;
	y_g = (float)y / 16380;
	z_g = (float)z / 16380;
}
