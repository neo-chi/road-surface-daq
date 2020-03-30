#include "accelerometer.h"

Accelerometer accelerometer;

void setup()
{
        // Setup debugging.
        delay(1000);           // UNIX
        Serial.begin(115200);  // debugging

        accelerometer.begin();

        Serial.printf("Reading pre_impact data...");
        accelerometer.read(PRE_IMPACT);
        Serial.printf("complete!\n");
        delay(2000);
        Serial.printf("Displaying data...\n");
        for (size_t i = 0; i < PRE_IMP_BUF_LEN; i++) {
                Serial.printf("%0.3f,%0.3f,%0.3f\n",
                              accelerometer.pre_impact[i].x,
                              accelerometer.pre_impact[i].y,
                              accelerometer.pre_impact[i].z);
        }
        Serial.printf("complete!\n");
        delay(2000);

        Serial.printf("Reading post_impact data...");
        accelerometer.read(POST_IMPACT);
        Serial.printf("complete!\n");
        delay(2000);
        Serial.printf("Displaying data...\n");
        for (size_t i = 0; i < POST_IMP_BUF_LEN; i++) {
                Serial.printf("%0.3f,%0.3f,%0.3f\n",
                              accelerometer.post_impact[i].x,
                              accelerometer.post_impact[i].y,
                              accelerometer.post_impact[i].z);
        }
        Serial.printf("complete!\n");
        delay(2000);
}

void loop()
{
        accelerometer_data acc = accelerometer.read();
        Serial.printf("%0.3f,%0.3f,%0.3f\n", acc.x, acc.y, acc.z);
        delay(1000);
}
