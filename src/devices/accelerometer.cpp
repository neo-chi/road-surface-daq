#include "accelerometer.h"

/**
 * Default constructor.
 **/
Accelerometer::Accelerometer()
{
        Serial.println("Created an accelerometer.");
}

/**
 * Returns a buffer of x, y, z acceleration data.
 *
 * @returns accelerometer_data
 **/
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

/**
 * Returns the size of the acceleration buffer.
 *
 * @return int acceleration buffer size.
 **/
int Accelerometer::size_buffer()
{
        Serial.printf("Getting size of accelerometer buffer.\n");
        return this->buffer_size;
}

/**
 * Allow the accelerometer to trigger interrupts again.
 **/
void Accelerometer::unlatch_interrupt()
{
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
