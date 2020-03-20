#include "wifi.h"

void setup()
{
        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200);  // debugging

        /** @test Constructor */
        WiFi wifi("__SSID__", "__PSK__");
        if (!wifi.is_connected()) {
                wifi.connect();
        }
        wifi.disconnect();
        wifi.set_ssid("fbi van");
        wifi.set_psk("agent_smith");
        wifi.connect(20000);

}

void loop()
{

}
