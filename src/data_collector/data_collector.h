#ifndef _ROAD_SURFACE_DAQ_DATACOLLECTER_H
#define _ROAD_SURFACE_DAQ_DATACOLLECTER_H

#include "Arduino.h"
// @require REQUIRES SENSOR LIBRARIES

enum class sensor_t : char {  // reduces memory requirement
  gps,
  accelerometer,
  enviormental
};

enum class gps_data_t : char {  // reduces memory requirement
  location,
  speed,
  date,
  time,
  datetime,
  travel
};

enum class accelerometer_data_t : char {  // reduces memory requirement
  x_acceleration,
  y_acceleration,
  z_acceleration
};

enum class environmental_data_t : char {  // reduces memory requirement
  temperature,
  humidity,
  pressure,
  altitude
};

class DataCollector { // Implements Observable --> getState of sensors... gps connected? accelerometer interrupt latched? environmental data sampling timer complete?
  public: // Interface for Mediator
    DataCollector();
    String* getDataBuffer(sensor_t sensor, void *sensor_data_type);
    String getData(sensor_t sensor, void *sensor_data_type);
  private:
    // void updateCache(sensor_t sensor, void *sensor_data_type, void *cache);
    // GPS gps;
    // Accelerometer accelerometer;
    // Environmental environmental;
    // Date date_cache;
    // Time time_cache;
    // Acceleration acceleration_buffer[SIZE_ACCELERATION_BUFFER];
    gps_data_t getGPSDataType(void *sensor_data_type);
    String getGPSData(void* gps_data_type);
    accelerometer_data_t getAccelerometerDataType(void* sensor_data_type);
    String getAccelerometerData(void* accelerometer_data_type);
    environmental_data_t getEnvironmentalDataType(void* sensor_data_type);
    String getEnvironmentalData(void* environmental_data_type);
};

#endif
