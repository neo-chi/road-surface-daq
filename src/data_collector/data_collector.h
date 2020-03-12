#ifndef _ROAD_SURFACE_DAQ_DATA_COLLECTER_H
#define _ROAD_SURFACE_DAQ_DATA_COLLECTER_H

#include "Arduino.h"
//#ifndef _ROAD_SURFACE_DAQ_DATA_COLLECTOR_EVENT_H
#include "data_collector_event.h"
//#endif
//#ifndef _ROAD_SURFACE_DAQ_MEDIATOR_H
//#include "mediator.h"
//#endif
// @require REQUIRES SENSOR LIBRARIES

enum class sensor_t : char {
  gps,
  accelerometer,
  enviormental
};

enum class gps_data_t : char {
  location,
  speed,
  date,
  time,
  datetime,
  travel
};

enum class accelerometer_data_t : char {
  x_acceleration,
  y_acceleration,
  z_acceleration
};

enum class environmental_data_t : char {
  temperature,
  humidity,
  pressure,
  altitude
};

class Mediator;
class DataCollector {
  public:
    DataCollector();
    void Attach(Mediator *mediator);
    void Notify(data_collector_event event);
    String* getDataBuffer(sensor_t sensor, void *sensor_data_type);
    String getData(sensor_t sensor, void *sensor_data_type);
  private:
    Mediator *mediator;
    String getGPSData(void* gps_data_type);
    String getAccelerometerData(void* accelerometer_data_type);
    String getEnvironmentalData(void* environmental_data_type);
    // void updateCache(sensor_t sensor, void *sensor_data_type, void *cache);
    // GPS gps;
    // Accelerometer accelerometer;
    // Environmental environmental;
    // Date date_cache;
    // Time time_cache;
    // Acceleration acceleration_buffer[SIZE_ACCELERATION_BUFFER];
};

#endif
