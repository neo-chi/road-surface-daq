#pragma once

#include "Arduino.h"
#include "WiFiClient.h"

#define SSID_SIZE_MAX 32
#define PSK_SIZE_MAX 32

class WiFi
{
        public:
                void connect(long timeout = 0);
                void disconnect();
                bool is_connected();
                void set_ssid(char *ssid);
                void set_psk(char *psk);
        private:
                char *ssid[SSID_SIZE_MAX];
                char *psk[PSK_SIZE_MAX];

};