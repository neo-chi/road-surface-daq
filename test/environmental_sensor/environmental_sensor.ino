#include "environmental_sensor.h"
#include "Wire.h"

EnvironmentalSensor environmental_sensor;


void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200); // Debugging
        /** @test */
        Wire.begin();
        environmental_sensor.driver.begin();
}

void loop()
{
        environmental_sensor.update_cache();
        environmental_data env_data = environmental_sensor.read();
        Serial.printf("----------------------\n");
        Serial.printf("Temperature: \t %0.3lf\n", env_data.temperature);
        Serial.printf("Humidity:    \t %0.3lf\n", env_data.humidity);
        Serial.printf("Pressure:    \t %0.3lf\n", env_data.pressure);
        Serial.printf("----------------------\n");
        delay(500);
}
