#include "storage.h"
#include "Adafruit_LIS3DH.h"
#include "accelerometer_data.h"

char input_buf[50000]; // 256kB
const size_t size_acceleration = 1600;
accelerometer_data acceleration[size_acceleration];

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200);  // debugging

        /** @test **/
        Storage storage;
	Adafruit_LIS3DH accelerometer;
	accelerometer.setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
	accelerometer.setRange(LIS3DH_RANGE_16_G);
	accelerometer.begin(LIS3DH_DEFAULT_ADDRESS);


        // write acceleration log as binary.
        //> populate acceleration array with data.
        for (size_t i = 0; i < size_acceleration - 1; i++) {
		accelerometer.read();
                acceleration[i].x = accelerometer.x_g;
                acceleration[i].y = accelerometer.y_g;
                acceleration[i].z = accelerometer.z_g;
        }
        //> view actual size of acceleration.
        Serial.printf("sizeof(acceleration)\t%u", sizeof(acceleration));

        // Generate data strings
        size_t bytes_written = 0;
        for (size_t i = 0; i < size_acceleration - 1; i++) {
                bytes_written += sprintf(input_buf + bytes_written, "%0.3f,%0.3f,%0.3f\n",
                        acceleration[i].x,
                        acceleration[i].y,
                        acceleration[i].z);
                Serial.printf("bytes_written: %u\n", bytes_written);
                //Serial.printf("content:\n%s\n\n", input_buf);
        }

        //> example write_acceleration_binary function
        storage.write("/write_buf.txt", (uint8_t*)input_buf, bytes_written);
        storage.read("/write_buf.txt");

        // storage.write("/write_buf.txt", (uint8_t*)input_buf, input_buf_len);
        // storage.read("/write_buf.txt");

}

void loop()
{

}
