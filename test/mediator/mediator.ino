#include "mediator.h"

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);

  // Test DataCollector construction
  DataCollector data_collector;

  // Test DataCollector.getData() --> gps.getTravel()
  gps_data_t gps_data_type = gps_data_t::travel;
  String travel = data_collector.getData(sensor_t::gps, &gps_data_type);
  String test_output = "Data received: ";
  test_output.concat(travel);
  Serial.println(test_output);

  // Test Datollect.getData() --> gps.getLocation()
  gps_data_t gps_location = gps_data_t::location;
  String location = data_collector.getData(sensor_t::gps, &gps_location);
  test_output.clear();
  test_output.concat("Data received: ");
  test_output.concat(location);
  Serial.println(test_output);

  // Test DataCollector.getData() --> gps.getDatetime()
  gps_data_type = gps_data_t::datetime;
  String data = data_collector.getData(sensor_t::gps, &gps_data_type);
  test_output.clear();
  test_output.concat("Data received: ");
  test_output.concat(data);
  Serial.println(test_output);

  accelerometer_data_t acc_data_type = accelerometer_data_t::x_acceleration;
  String x_acceleration = data_collector.getData(
    sensor_t::accelerometer, &acc_data_type);
  String print_output = "Data received: ";
  print_output.concat(x_acceleration);
  Serial.println(print_output);

  acc_data_type = accelerometer_data_t::y_acceleration;
  String y_acceleration = data_collector.getData(
    sensor_t::accelerometer, &acc_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(y_acceleration);
  Serial.println(print_output);

  acc_data_type = accelerometer_data_t::z_acceleration;
  String z_acceleration = data_collector.getData(
    sensor_t::accelerometer, &acc_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(y_acceleration);
  Serial.println(print_output);

  environmental_data_t env_data_type = environmental_data_t::temperature;
  String temperature = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(temperature);
  Serial.println(print_output);

  env_data_type = environmental_data_t::humidity;
  String humidity = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(humidity);
  Serial.println(print_output);

  env_data_type = environmental_data_t::pressure;
  String pressure = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(pressure);
  Serial.println(print_output);

  env_data_type = environmental_data_t::altitude;
  String altitude = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(altitude);
  Serial.println(print_output);
}


void loop() {

}
