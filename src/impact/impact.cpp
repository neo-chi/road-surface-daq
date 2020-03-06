#include "impact.h"

// The impact class is responsible for recording data relevant to an impact
// event triggered by the accelerometer interrupt signal.
// Each impact is tagged with:
//   Datetime : YYYYMMDD HHMMSS
//   Location : Latitude (0.6lf), Longitude (0.6lf)
//   is_pothole: boolean true --> differentiates Travel logs from Impact logs.
Impact::Impact(Datetime _datetime, Location _location) : datetime(_datetime) {
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
  return log_string;
}

String Impact::toUploadString() {

  // Format datetime to POST format
  String datetime_string = "datetime=";
  datetime_string.concat(datetime.date.year);
  datetime_string.concat("-");
  datetime_string.concat(datetime.date.month);
  datetime_string.concat("-");
  datetime_string.concat(datetime.date.day);
  datetime_string.concat("+");
  datetime_string.concat(datetime.time.hour);
  datetime_string.concat("\\%3A");
  datetime_string.concat(datetime.time.minute);
  datetime_string.concat("\\%3A");
  datetime_string.concat(datetime.time.second);

  // Format latitude to POST format
  String latitude_string = "latitude=";
  char formatted_latitude[15];
  sprintf(formatted_latitude, "%0.6lf", location.latitude);
  latitude_string.concat(formatted_latitude);

  // Format longitude to POST format
  String longitude_string = "longitude=";
  char formatted_longitude[15];
  sprintf(formatted_longitude, "%0.6lf", location.longitude);
  longitude_string.concat(formatted_longitude);

  // Format severity to POST format
  String severity_string = "is-pothole=1";

  // Concatenate the above strings to get complete POST string
  String upload_string = "";
  upload_string.concat(datetime_string);
  upload_string.concat("&");
  upload_string.concat(latitude_string);
  upload_string.concat("&");
  upload_string.concat(longitude_string);
  upload_string.concat("&");
  upload_string.concat(severity_string);

  return upload_string;
}
