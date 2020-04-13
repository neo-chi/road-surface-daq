/*******************************************************************************
 * @file	wifi.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
#include "wifi.h"

/**
 * WiFi Constructor.
 *
 * @param ssid: network name.
 * @param psk: network password.
 *
 * @returns WiFi object
 **/
WiFiManager::WiFiManager(char *ssid, char *psk)
{
        this->set_ssid(ssid);
        this->set_psk(psk);
        Serial.println("Created a WiFi connector.");
}

void WiFiManager::begin()
{
}

/**
 * Attempt WiFi connection.
 *
 * @param timeout: end connection attempt after time in milliseconds.
 **/
void WiFiManager::connect(long timeout) {
        // Display network details.
        Serial.print("Connecting to WiFi: ");
        Serial.printf("SSID:\t%s\t", this->_network_conf.ssid);
        Serial.printf("PSK:\t%s\n", this->_network_conf.psk);

        if (this->is_connected())
                return;

        WiFi.mode(WIFI_OFF);
        WiFi.mode(WIFI_STA);
        WiFi.begin(this->_network_conf.ssid, this->_network_conf.psk);
        // Connection attempt **WITH** timeout.
        if (timeout > 0) {
                long elapsed_time = 0;
                int seconds_waiting = 0;
                Serial.print("Attempting connection...");
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
                                break;
                        }
                }  // A connection was **SUCCESSFUL**.
                if (this->is_connected()) {
                        Serial.println("WiFi connected!");
                } else {
                        Serial.println("WiFi connection failed!");
                        WiFi.disconnect();
                }
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
void WiFiManager::disconnect()
{
        WiFi.mode(WIFI_OFF);
        Serial.println("WiFi disconnected!");
}

/**
 * Check WiFi connectivity
 *
 * @returns bool
 **/
bool WiFiManager::is_connected()
{
        if (WiFi.status() == WL_CONNECTED)
                return true;
        else
                return false;
}

/**
 * Update network name.
 *
 * @param ssid wifi network name.
 **/
void WiFiManager::set_ssid(char *ssid)
{
        Serial.printf("Updated WiFi SSID to %s\n", ssid);
        strcpy(this->_network_conf.ssid, ssid);
}

/**
 * Update network password.
 *
 * @param psk wifi network password.
 */
void WiFiManager::set_psk(char *psk)
{
        Serial.printf("Updated WiFi PSK to %s\n", psk);
        strcpy(this->_network_conf.psk, psk);
}

