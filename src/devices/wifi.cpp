#include "wifi.h"

/**
 * WiFi Constructor.
 *
 * @param ssid: network name.
 * @param psk: network password.
 *
 * @returns WiFi object
 **/
WiFi::WiFi(char *ssid, char *psk)
{
        this->set_ssid(ssid);
        this->set_psk(psk);
        Serial.println("Created a WiFi connector.");
}
/**
 * Attempt WiFi connection.
 *
 * @param timeout: end connection attempt after time in milliseconds.
 **/
void WiFi::connect(long timeout)
{
        // Display network details.
        Serial.println("Connecting to WiFi: ");
        Serial.printf("SSID:\t%s\n", this->network_conf.ssid);
        Serial.printf("PSK:\t%s\n", this->network_conf.psk);

        // Connection attempt **WITH** timeout.
        if (timeout > 0) {
                long elapsed_time = 0;
                int seconds_waiting = 0;
                Serial.println("Attempting connection");
                while (!this->is_connected()) {
                        if (millis() - elapsed_time > 1000) {  // Print "." every second.
                                Serial.print(".");
                                elapsed_time = millis();
                                seconds_waiting++;
                        }
                        if (seconds_waiting > 10) {  // Begin a newline every 10 seconds.
                                Serial.println();
                                seconds_waiting = 0;
                        }
                        if (elapsed_time > timeout) {  // Connection was **UNSUCCESSFUL**.
                                Serial.println("Connection attempt failed");
                                break;
                        }
                }  // A connection was **SUCCESSFUL**.
                Serial.println("WiFi connected!");
        // Connection attempt **WITHOUT** timout.
        } else {
                long elapsed_time = 0;
                int seconds_waiting = 0;
                Serial.println("Attempting connection");
                while (!this->is_connected()) {
                        if (millis() - elapsed_time > 1000) {  // Print "." every second.
                                Serial.print(".");
                                elapsed_time = millis();
                                seconds_waiting++;
                        }
                        if (seconds_waiting > 10) {  // Begin a newline every 10 seconds.
                                Serial.println();
                                seconds_waiting = 0;
                                break; // FIXME: remove this, for testing only.
                        }
                }  // A connection was **SUCCESSFUL**.
                Serial.println("WiFi connected!");
        }
}

/**
 * Disable WiFi.
 **/
void WiFi::disconnect()
{
        Serial.println("WiFi disconnected!");
}

/**
 * Check WiFi connectivity
 *
 * @returns bool
 **/
bool WiFi::is_connected()
{
        return false;
}

/**
 * Update network name.
 *
 * @param ssid wifi network name.
 **/
void WiFi::set_ssid(char *ssid)
{
        Serial.printf("Updated WiFi SSID to %s\n", ssid);
        strcpy(this->network_conf.ssid, ssid);
}

/**
 * Update network password.
 *
 * @param psk wifi network password.
 */
void WiFi::set_psk(char *psk)
{
        Serial.printf("Updated WiFi PSK to %s\n", psk);
        strcpy(this->network_conf.psk, psk);

}
