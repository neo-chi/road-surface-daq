#ifndef _ROAD_SURFACE_DAQ_STORAGE_EVENT_H
#define _ROAD_SURFACE_DAQ_STORAGE_EVENT_H

#include "Arduino.h"

enum class storage_event : char {
  file_write_success,
  file_write_failure,
  file_read_success,
  file_read_failure
};

#endif
