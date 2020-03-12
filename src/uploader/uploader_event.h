#ifndef _ROAD_SURFACE_DAQ_UPLODAER_EVENT_H
#define _ROAD_SURFACE_DAQ_UPLODAER_EVENT_H

#include "Arduino.h"

enum class uploader_event : char {
  wifi_connected,
  wifi_disconnected,
  upload_success,
  upload_failure
};

#endif
