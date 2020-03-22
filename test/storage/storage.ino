#include "storage.h"
#include "accelerometer_data.h"

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200);  // debugging

        /** @test **/
        Storage storage;

        storage.rm("/write_buf");
        storage.rm("/write_buf.txt");

        storage.mkdir("/test");
        storage.write("/test/impact.imp", "Hello!\n");
        storage.write("/test/impact.imp", "Hello!\n");
        storage.write("/test/impact.imp", "Goodbye!\n");
        storage.write("/test/impact.imp", "Goodbye!\n");
        storage.write("/test/impact.imp", "Goodbye!\n");
        storage.write("/test/impact.imp", "Oranges!\n");
        storage.write("/test/impact.imp", "Oranges!\n");
        storage.write("/test/impact.imp", "Oranges!\n");
        storage.write("/test/impact.imp", "Oranges!\n");
        storage.write("/test/impact.imp", "Oranges!\n");
        storage.read("/test/impact.imp");
        storage.mv("/test/impact.imp", "/impact.imp");
        storage.read("/impact.imp");
        storage.rm("/impact.imp");
        storage.rmdir("/test");

        //> initialize buffer

        size_t of_char = sizeof(char);
        size_t of_uint8_t = sizeof(uint8_t);
        size_t of_char_ptr = sizeof(char*);
        size_t of_uint8_t_ptr = sizeof(uint8_t*);
        Serial.printf("sizeof(char)\t\t%u\n", of_char);
        Serial.printf("sizeof(uint8_t)\t\t%u\n", of_uint8_t);
        Serial.printf("sizeof(char*)\t\t%u\n", of_char_ptr);
        Serial.printf("sizeof(uint8_t*)\t%u\n", of_uint8_t_ptr);

        // write acceleration log as binary.
        const size_t size_acceleration = 30;
        accelerometer_data acceleration[size_acceleration];
        //> populate acceleration array with data.
        for (size_t i = 0; i < size_acceleration - 1; i++) {
                acceleration[i].x = i;
                acceleration[i].y = i * 2;
                acceleration[i].z = i * 3;
        }
        //> view actual size of acceleration.
        Serial.printf("sizeof(acceleration)\t%u", sizeof(acceleration));

        // Generate data strings
        char input_buf[2048]; // 256kB
        size_t bytes_written = 0;
        for (size_t i = 0; i < size_acceleration - 1; i++) {
                bytes_written += sprintf(input_buf + bytes_written, "x: %0.3f, y: %0.3f, z: %0.3f\n",
                        acceleration[i].x,
                        acceleration[i].y,
                        acceleration[i].z);
                Serial.printf("bytes_written: %u\n", bytes_written);
                Serial.printf("content:\n%s\n\n", input_buf);
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
