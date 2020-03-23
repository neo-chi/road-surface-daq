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
        for (int i = 0; i < BUF_LEN; i++) {
		//driver.read();
                buffer[i].x = driver.x_g;
                buffer[i].y = driver.y_g;
                buffer[i].z = driver.z_g;
        }
        Serial.print("Complete!\n");
	//Serial.print(buf);
        return buffer;
}

/**
 * Returns the size of the acceleration buffer.
 *
 * @return int acceleration buffer size.
 **/
int Accelerometer::size_buffer()
{
        //Serial.printf("Getting size of accelerometer buffer.\n");
        return buffer_size;
}

/**
 * Allow the accelerometer to trigger interrupts again.
 **/
void Accelerometer::unlatch_interrupt()
{
	driver.configurationRead(INT1_SRC);
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
