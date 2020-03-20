#include "accelerometer.h"

Accelerometer::Accelerometer()
{
        Serial.println("Created an accelerometer.");
}

accelerometer_data *Accelerometer::read()
{
        Serial.printf("Reading acceleromter...");
        for (int i = 0; i < 512; i++) {
                float x = 1 * i;
                float y = 2 * i;
                float z = 3 * i;
                this->buffer[i].x = x;
                this->buffer[i].y = y;
                this->buffer[i].z = z;
        }
        Serial.print("Complete!\n");
        return this->buffer;
}

int Accelerometer::size_buffer()
{
        Serial.printf("Getting size of accelerometer buffer.\n");
        return this->buffer_size;
}

void Accelerometer::unlatch_interrupt()
{
        Serial.printf("Unlactched interrupt!\n");
}

bool Accelerometer::interrupt_is_latched()
{
        Serial.printf("Accelerometer buffer is latched.");
        return true;
}

bool Accelerometer::buffer_is_full()
{
        Serial.printf("Accelerometer buffer is full!");
        return true;
}
