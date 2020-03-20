#include "environmental_sensor.h"

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200); // Debugging

        /** @test */
        EnvironmentalSensor environmental_sensor;
        environmental_data env_data = environmental_sensor.read();
        printf("Temperature: \t %0.3lf\n", env_data.temperature);
        printf("Humidity: \t %0.3lf\n", env_data.humidity);
        printf("Pressure: \t %0.3lf\n", env_data.pressure);
        printf("Altitude: \t %0.3lf\n", env_data.altitude);
}

void loop()
{

}
