/*******************************************************************************
 * @file	wifi.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * The WiFiManager class is responsible for controlling WiFI connections and
 * WiFi connection configurations.
 *
 * This class features:
 *      - WiFi connection with optional timeout
 *      - WiFi disconnection and disabling
 *      - Setting SSID and passkey
 *
 * The WiFiManager implements a driver native to the ESP32 and therefore, will
 * not need any additional libraries beyond those developed by espressif.
*******************************************************************************/
#pragma once

#include "Arduino.h"
#include "WiFi.h"
#include "WiFiClient.h"

#define SSID_SIZE_MAX 32
#define PSK_SIZE_MAX 32

class WiFiManager
{
        public:
                WiFiManager(char *ssid, char*psk);
                void begin();
                void connect(long timeout = 0);
                void disconnect();
                bool is_connected();
                void set_ssid(char *ssid);
                void set_psk(char *psk);
        private:
                WiFiClient _driver;
                struct network_conf {
                        char ssid[SSID_SIZE_MAX];
                        char psk[PSK_SIZE_MAX];
                } _network_conf;
};
