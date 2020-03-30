#include "impact_controller.h"
#include "accelerometer.h"
#include "environmental_sensor.h"
#include "gps.h"

void setup()
{
        /// Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200);  // Debugging

        // SECTION - setup devices
        Accelerometer accelerometer;
        EnvironmentalSensor environmental_sensor;
        GPS gps;
        // #SECTION - setup devices

        // Test impact controller constructor.
        ImpactController *impact_controller = new ImpactController;

        // Test impact controller impact creation.
        //* Setup data *//
        accelerometer_data *_accelerometer_data = accelerometer.read();
        environmental_data _environmenatal_data = environmental_sensor.read();
        gps_data _gps_data = gps.read();
        int length_acceleration_buffer = accelerometer.size_buffer();
        //* Test Creation *//
        impact_data _impact_data = impact_controller->create_impact(_gps_data,
                _environmenatal_data,
                _accelerometer_data,
                length_acceleration_buffer);

        Storage storage; // [ ] move me to @setup devices
        impact_controller->log_impact(storage, _impact_data);
}

void loop()
{

}
