/*******************************************************************************
 * @file	wifi.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-26
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
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
                void            connect(long timeout = 0);
                void            disconnect();
                bool            is_connected();
                void            set_ssid(char *ssid);
                void            set_psk(char *psk);
        private:
                WiFiClient      driver;
                struct network_conf {
                        char ssid[SSID_SIZE_MAX];
                        char psk[PSK_SIZE_MAX];
                } network_conf;
};
