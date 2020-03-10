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

  // Test DataCollector.getData() --> accelerometer.getX()
  accelerometer_data_t acc_data_type = accelerometer_data_t::x_acceleration;
  String x_acceleration = data_collector.getData(
    sensor_t::accelerometer, &acc_data_type);
  String print_output = "Data received: ";
  print_output.concat(x_acceleration);
  Serial.println(print_output);

  // Test DataCollect.getData() --> accelerometer.getY()
  acc_data_type = accelerometer_data_t::y_acceleration;
  String y_acceleration = data_collector.getData(
    sensor_t::accelerometer, &acc_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(y_acceleration);
  Serial.println(print_output);

  // Test DataCollector.getData() --> accelerometer.getZ()
  acc_data_type = accelerometer_data_t::z_acceleration;
  String z_acceleration = data_collector.getData(
    sensor_t::accelerometer, &acc_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(y_acceleration);
  Serial.println(print_output);

  // Test DataCollector.getData() --> enviormental.getTemperature()
  environmental_data_t env_data_type = environmental_data_t::temperature;
  String temperature = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(temperature);
  Serial.println(print_output);

  // Test DataCollector.getData() --> enviormental.getHumidity()
  env_data_type = environmental_data_t::humidity;
  String humidity = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(humidity);
  Serial.println(print_output);

  // Test DataCollector.getData() --> enviormental.getPressure()
  env_data_type = environmental_data_t::pressure;
  String pressure = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(pressure);
  Serial.println(print_output);

  // Test DataCollector.getData() --> enviormental.getAltitude()
  env_data_type = environmental_data_t::altitude;
  String altitude = data_collector.getData(
    sensor_t::enviormental,
    &env_data_type);
  print_output.clear();
  print_output.concat("Data received: ");
  print_output.concat(altitude);
  Serial.println(print_output);

  // Investigate String Buffer.
  Serial.println();
  Serial.println();
  String buffer[512];
  Serial.printf("Size of buffer = %d", sizeof(buffer));
  Serial.println();

  // Write to buffer
  int buffer_ptr = 0;
  buffer[buffer_ptr] = "Hi!\n";
  buffer[++buffer_ptr]= "My name is Reece.\n";
  buffer[++buffer_ptr]= "Chocolate is tasty.\n";

  // Display buffer contents
  for (int bufferIdx = 0; bufferIdx < 512; bufferIdx++) {
    Serial.print(buffer[bufferIdx]);
  }

  // Clear buffer
  for (int bufferIdx = 0; bufferIdx < 512; bufferIdx++) {
    buffer[bufferIdx] = "";
  }

  // Display buffer contents
  for (int bufferIdx = 0; bufferIdx < 512; bufferIdx++) {
    Serial.print(buffer[bufferIdx]);
  }

  // Storage Write single string.
  Storage storage;
  storage.write("/", travel);

  // Test storge write buffer
  buffer_ptr = 0;
  buffer[buffer_ptr] = temperature;
  buffer[++buffer_ptr] = humidity;
  buffer[++buffer_ptr] = pressure;
  buffer[++buffer_ptr] = altitude;
  buffer[++buffer_ptr] = x_acceleration;
  buffer[++buffer_ptr] = y_acceleration;
  buffer[++buffer_ptr] = z_acceleration;
  buffer[++buffer_ptr] = location;
  buffer[++buffer_ptr] = travel;
  storage.write("/", buffer, 512);

  // Test storage mkdir (make directory)
  storage.mkdir("/20200311");

  // Test storage rename (move)
  storage.rename("/20200311/092103.imp", "/uploaded/092103.imp");

  // Test storage remove
  storage.remove("/uploaded/092103.imp");
}


void loop() {

}
