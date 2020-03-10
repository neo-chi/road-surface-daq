#include "data_collector.h"

// The Data collector class is responsible for getting data from external
// sensors in the form of a String, or a String buffer.
DataCollector::DataCollector() {
  Serial.println("Constructed a DataCollector");
}

String DataCollector::getData(sensor_t sensor, void *sensor_data_type) {
  switch (sensor) {
    case (sensor_t::gps):
      return getGPSData(sensor_data_type);
    case (sensor_t::accelerometer):
      return getAccelerometerData(sensor_data_type);
    case (sensor_t::enviormental):
      return getEnvironmentalData(sensor_data_type);
    default:
      return "";  // @Note Unhandled sensor type
  }
}

String DataCollector::getGPSData(void* gps_data_type) {
  switch (getGPSDataType(gps_data_type)) {
    case gps_data_t::location:
      Serial.println("Getting GPS location...");
      return "35.897,-87.533";
    case gps_data_t::speed:
      Serial.println("Getting GPS speed...");
      return "529";
    case gps_data_t::date:
      Serial.println("Getting GPS date...");
      return "2020-02-03";
    case gps_data_t::time:
      Serial.println("Getting GPS time...");
      return "12:05:44";
    case gps_data_t::datetime:
      Serial.println("Getting GPS datetime...");
      return "2020-02-03,12:05:44";
    case gps_data_t::travel:
      Serial.println("Getting GPS travel...");
      return "2020-02-03,12:05:44,35.897,-87.533";
    default:
      return "";  // Unhandled Type
  }
}

gps_data_t DataCollector::getGPSDataType(void* sensor_data_type) {
  gps_data_t gps_data_type = *(gps_data_t *)sensor_data_type;
  return gps_data_type;
}

String DataCollector::getAccelerometerData(void* accelerometer_data_type) {
  switch (getAccelerometerDataType(accelerometer_data_type)) {
    case accelerometer_data_t::x_acceleration:
      Serial.println("Getting accelerometer x acceleration...");
      return "0.229837";
    case accelerometer_data_t::y_acceleration:
      Serial.println("Getting accelerometer y acceleration...");
      return "-0.188201";
    case accelerometer_data_t::z_acceleration:
      Serial.println("Getting accelerometer z acceleration...");
      return "1.350662";
    default:
      return "";
  }
}

accelerometer_data_t DataCollector::getAccelerometerDataType(
    void* sensor_data_type) {
  accelerometer_data_t accelerometer_data_type =
    *(accelerometer_data_t *)sensor_data_type;
  return accelerometer_data_type;
}

String DataCollector::getEnvironmentalData(void* environmental_data_type) {
  switch (getEnvironmentalDataType(environmental_data_type)) {
    case environmental_data_t::temperature:
      Serial.println("Getting environmental temperature...");
      return "72.898";
    case environmental_data_t::humidity:
      Serial.println("Getting environmental humidity...");
      return "0.159";
    case environmental_data_t::pressure:
      Serial.println("Getting environmental pressure...");
      return "1.001";
    case environmental_data_t::altitude:
      Serial.println("Getting environmental altitude...");
      return "345.201";
    default:
      return "";
  }
}

environmental_data_t DataCollector::getEnvironmentalDataType(
    void* sensor_data_type) {
  environmental_data_t environmental_data_type =
    *(environmental_data_t *)sensor_data_type;
  return environmental_data_type;
}
