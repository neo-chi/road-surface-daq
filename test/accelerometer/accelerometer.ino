#include "accelerometer.h"

void setup()
{
        // Setup debugging.
        delay(1000);           // UNIX
        Serial.begin(115200);  // debugging

        /** @test */
        Accelerometer *accelerometer = new Accelerometer;
        accelerometer_data *acceleration_ptr;

        if (accelerometer->interrupt_is_latched()) {
                if (accelerometer->buffer_is_full())
                        acceleration_ptr = accelerometer->read();
                accelerometer->unlatch_interrupt();
        }

        for (int i = 0; i < accelerometer->size_buffer(); i++) {
                printf("x: %0.3lf \t y: %0.3lf \t z: %0.3lf\n",
                        acceleration_ptr->x,
                        acceleration_ptr->y,
                        acceleration_ptr->z);
                ++acceleration_ptr;
        }

}

void loop()
{

}