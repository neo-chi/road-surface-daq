#ifndef _ROAD_SURFACE_DAQ_UPLOADER_H
#define _ROAD_SURFACE_DAQ_UPLOADER_H

#include "Arduino.h"
// @reqiure WiFiClient.h
// @require HttpClient.h

class Uploader {  // @note Implements Observable
  public:
    Uploader();
    void Upload(const String& location_header, const String& post_data);
  private:
    // WiFiClient wifi;
    // HttpClient http;
    // bool EnableWiFi();
    // bool DisableWiFi();
    // bool WaitForWiFiConnection(long timeout);
};

#endif
