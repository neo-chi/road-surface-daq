#include "Adafruit_LIS3DH.h"

Adafruit_LIS3DH acc;

struct acc_data {
	float x;
	float y;
	float z;
} acc_data_t;

char log_buf[16384];
char log_buf2[16384];
char log_buf3[16384];
size_t buf_len = 0;
size_t buf2_len = 0;
size_t buf3_len = 0;
void setup()
{
        // Setup debugging.
        delay(1000);           // UNIX
        Serial.begin(115200);  // debugging
	acc.setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
	acc.setRange(LIS3DH_RANGE_8_G);
	acc.printSensorDetails();

	//char log_buf3[4096];

	// Read accelerometer data to buffer.
	const int acc_buf_len = 512;
	acc_data acc_data_buf[acc_buf_len];
	size_t bytes_written = 0;
	for (int i = 0; i < acc_buf_len; i++) {
		acc.read();
		acc_data_buf[i].x = acc.x_g;
		acc_data_buf[i].y = acc.y_g;
		acc_data_buf[i].z = acc.z_g;
	}
	// Now lets get a log string.
	for (int i = 0; i < acc_buf_len; i++) {
		bytes_written = sprintf(log_buf + buf_len, "x: %0.3f\ty: %0.3f\tz: %0.3f\n",
					acc_data_buf[i].x,
					acc_data_buf[i].y,
					acc_data_buf[i].z);
		buf_len += bytes_written;
	}

	// Read accelerometer data to buffer.
	for (int i = 0; i < acc_buf_len; i++) {
		acc.read();
		acc_data_buf[i].x = acc.x_g;
		acc_data_buf[i].y = acc.y_g;
		acc_data_buf[i].z = acc.z_g;
	}

	// Now lets get a log string.
	for (int i = 0; i < acc_buf_len; i++) {
		bytes_written = sprintf(log_buf2 + buf2_len, "x: %0.3f\ty: %0.3f\tz: %0.3f\n",
					acc_data_buf[i].x,
					acc_data_buf[i].y,
					acc_data_buf[i].z);
		buf2_len += bytes_written;
	}

	// Read accelerometer data to buffer.
	for (int i = 0; i < acc_buf_len; i++) {
		acc.read();
		acc_data_buf[i].x = acc.x_g;
		acc_data_buf[i].y = acc.y_g;
		acc_data_buf[i].z = acc.z_g;
	}

	// Now lets get a log string.
	for (int i = 0; i < acc_buf_len; i++) {
		bytes_written = sprintf(log_buf3 + buf3_len, "x: %0.3f\ty: %0.3f\tz: %0.3f\n",
					acc_data_buf[i].x,
					acc_data_buf[i].y,
					acc_data_buf[i].z);
		buf3_len += bytes_written;
	}

	Serial.print(log_buf);
	Serial.print(log_buf2);
	Serial.print(log_buf3);
	Serial.printf("Size of log_buf: %u\n", buf_len);
	Serial.printf("Bytes of last write: %u\n", bytes_written);


}

void loop()
{
	acc.read();
	Serial.printf("x: %0.3f\t y:%0.3f\tz: %0.3f\n", acc.x_g, acc.y_g, acc.z_g);
	delay(200);
}

