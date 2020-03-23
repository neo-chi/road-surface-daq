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
	// Configure acclerometer control registers.
	configurationWrite(CTRL_REG1,     CTRL_REG1_CONFIGURATION);
	configurationWrite(CTRL_REG2,     CTRL_REG2_CONFIGURATION);
	configurationWrite(CTRL_REG3,     CTRL_REG3_CONFIGURATION);
	configurationWrite(CTRL_REG4,     CTRL_REG4_CONFIGURATION);
	configurationWrite(CTRL_REG5,     CTRL_REG5_CONFIGURATION);
	configurationWrite(FIFO_CTRL_REG, FIFO_CTRL_REG_CONFIGURATION);
	configurationWrite(INT1_CFG,      INT1_CFG_CONFIGURATION);
	configurationWrite(INT1_THS,      INT1_THS_CONFIGURATION);
	configurationWrite(INT1_DURATION, INT1_DURATION_CONFIGURATION);
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
//void LIS3DH::read_int16()
//{
	//Wire.beginTransmission(LIS3DH_SLAVE_ADDRESS);
	//Wire.write(OUT_X_L | 0x80); // 0x80 -> autoincrement

	//if (Wire.endTransmission() != 0) {
		//Serial.println("LIS3DH Read Error");
		//return;
	//}
	//delayMicroseconds(50);


	//Wire.requestFrom(LIS3DH_SLAVE_ADDRESS, 6);
	//delayMicroseconds(50);

	//x = Wire.read() | Wire.read() << 8;
	//y = Wire.read() | Wire.read() << 8;
	//z = Wire.read() | Wire.read() << 8;
//}

//void LIS3DH::read_float()
//{
	//Wire.beginTransmission(LIS3DH_SLAVE_ADDRESS);
	//Wire.write(OUT_X_L | 0x80); // 0x80 -> autoincrement

	//if (Wire.endTransmission() != 0) {
		//Serial.println("LIS3DH Read Error");
		//return;
	//}
	//delayMicroseconds(50);


	//Wire.requestFrom(LIS3DH_SLAVE_ADDRESS, 6);
	//delayMicroseconds(50);

	//x_g = (float)(Wire.read() | Wire.read() << 8);
	//y_g = (float)(Wire.read() | Wire.read() << 8);
	//z_g = (float)(Wire.read() | Wire.read() << 8);
//}


void LIS3DH::read_float(float *x_buf, float *y_buf, float *z_buf, size_t len)
{
	uint16_t address = (uint16_t)LIS3DH_SLAVE_ADDRESS;
	uint8_t  num_bytes = 6;
	bool send_stop = false;
	Wire.beginTransmission(LIS3DH_SLAVE_ADDRESS);
	for (int i = 0; i < len - 1; i++) {
		Wire.write(OUT_X_L | 0x80);
		Wire.endTransmission();
		delayMicroseconds(50);
		Wire.requestFrom(address, num_bytes);
		delayMicroseconds(50);

		Serial.printf("%d = Wire.available()\n", Wire.available());

		if (Wire.available() <= 6) {
			uint8_t x_raw[2];
			Wire.readBytes(x_raw, 2);
			int16_t x = (x_raw[0] | x_raw[1] << 8);
			Serial.printf("0x%X\n", x);
			//int16_t x = Wire.read();
			//x |= (uint16_t)Wire.read() << 8;
			*x_buf = x / 15656;
			//*x_buf = (float)(Wire.read() | Wire.read() << 8);
			int16_t y = Wire.read() | Wire.read() << 8;
			*y_buf = y;

			int16_t z = Wire.read() | Wire.read() << 8;
			*z_buf = z;
			//Serial.printf("%d\n", x);
			//Serial.printf("%d\n", y);
			//Serial.printf("%d\n", z);
			//Serial.printf("%0.3f", *x_buf);
			++x_buf;
			++y_buf;
			++z_buf;
		}

		//Serial.println(*x_buf);
		//Serial.println(*y_buf);
		//Serial.println(*z_buf);
	}
	Wire.write(OUT_X_L | 0x80);
	Wire.endTransmission();
	Wire.requestFrom(address, num_bytes);
	*x_buf = (float)(Wire.read() | Wire.read() << 8);
	*y_buf = (float)(Wire.read() | Wire.read() << 8);
	*z_buf = (float)(Wire.read() | Wire.read() << 8);
	//Serial.println(*y_buf);
	//Serial.println(*z_buf);
}
