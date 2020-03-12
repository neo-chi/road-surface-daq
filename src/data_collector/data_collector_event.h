#ifndef _ROAD_SURFACE_DAQ_DATA_COLLECTOR_EVENT_H
#define _ROAD_SURFACE_DAQ_DATA_COLLECTOR_EVENT_H

#include "Arduino.h"

enum class data_collector_event : char {
  travel_buffer_full,
  impact_buffer_full,
  accelerometer_buffer_full,
  environment_buffer_full,
  gps_satellite_connected,
  gps_satellite_disconnected,
  accelerometer_interrupt_latched,
  accelerometer_interrupt_unlatched,
};

#endif
