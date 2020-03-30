#include "wifi.h"

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200);  // debugging

        WiFiManager wifi("FBI van 1", "2059030897");
        wifi.connect(15000);

        wifi.set_ssid("FBI van 2");
        wifi.connect(30000);

        delay(1000);
        Serial.printf("Disconnecting from network...");
        wifi.disconnect();
}

void loop()
{

}
