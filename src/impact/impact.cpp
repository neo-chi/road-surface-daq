#include "impact.h"

// The impact class is responsible for recording data relevant to an impact
// event triggered by the accelerometer interrupt signal.
// Each impact is tagged with:
//   Datetime : YYYYMMDD HHMMSS
//   Location : Latitude (0.6lf), Longitude (0.6lf)
//   is_pothole: boolean true --> differentiates Travel logs from Impact logs.
Impact::Impact(Datetime _datetime, Location _location) {
  datetime = _datetime;
  location = _location;
  Serial.println("Constructed an impact");  // Debugging
}

// The method toLogString returns impact data formatted for upload to a log file.
// This log string contains the following:
//   Datetime : YYYYMMDD HHMMSS
//   Location : Latitude (0.6lf), Longitude (0.6lf)
//   is_pothole: boolean true --> differentiates Travel logs from Impact logs.
// The string is returned in CSV format to allow for easy delimination of
// values for uploading.
// @Log String Format: YYYYMMDD HHMMSS,LATITUDE,LONGITUDE,1
String Impact::toLogString() {
  String log_string = "";
  log_string.concat(datetime.toString());
  log_string.concat(",");
  log_string.concat(location.toString());
  log_string.concat(",");
  log_string.concat("1");
  return log_string;
}

