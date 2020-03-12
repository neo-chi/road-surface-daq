#ifndef _ROAD_SURFACE_DAQ_UPLOADER_H
#define _ROAD_SURFACE_DAQ_UPLOADER_H

#include "Arduino.h"
#include "uploader_event.h"
// @reqiure WiFiClient.h
// @require HttpClient.h

class Mediator;
class Uploader {  // @note Implements Observable
  public:
    Uploader();
    void Attach(Mediator mediator);
    void Upload(const String& location_header, const String& post_data);
  private:
    Mediator *mediator;
    // WiFiClient wifi;
    // HttpClient http;
    // bool EnableWiFi();
    // bool DisableWiFi();
    // bool WaitForWiFiConnection(long timeout);
};

#endif
