#include "impact.h"

// The impact class is responsible for recording data relevant to an impact
// event triggered by the accelerometer interrupt signal.
// Each impact is tagged with:
//   Datetime : YYYYMMDD HHMMSS
//   Location : Latitude (0.6lf), Longitude (0.6lf)
//   is_pothole: boolean true --> differentiates Travel logs from Impact logs.
Impact::Impact(Datetime _datetime, Location _location)
             : datetime(_datetime), location(_location) {
  // Nothing to do here.
}

// The method toLogString returns impact data formatted for upload to a log file.
// This log string contains the following:
//   Datetime : YYYYMMDD HHMMSS
//   Location : Latitude (0.6lf), Longitude (0.6lf)
//   is_pothole: boolean true --> differentiates Travel logs from Impact logs.
// The string is returned in CSV format to allow for easy delimination of
// values for uploading.
// Log String Format: YYYYMMDD HHMMSS,LATITUDE,LONGITUDE,1
String Impact::toLogString() {
  String log = "";
  log.concat(datetime.toLogString());
  log.concat(location.toLogString());
  return log;
}

// Upload String Format:
// datetime=YYYY-MM-DD+HH\%3AMM\%3ASS&latitude=LATITUDE&longitude=LONGITUDE&is-pothole=1
String Impact::toUploadString() {
  const String SEVERITY = "is-pothole=1";  // TODO: update this to accept an enum

  // Format severity to POST format
  String upload_string = "";
  upload_string.concat(datetime.toUploadString());
  upload_string.concat("&");
  upload_string.concat(location.toUploadString());
  upload_string.concat("&");
  upload_string.concat(SEVERITY);

  return upload_string;
}
