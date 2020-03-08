#include "datetime.h"

// The Datetime class contains a date and time object that may be accessed
// individually and have their logging and upload Strings obtained.
Datetime::Datetime(Date _date, Time _time) : date(_date), time(_time) {
  date = _date;
  time = _time;
}

// Return the String date filename YYYYMMDD
String Datetime::toDateFileName() {
  return date.toFileNameString();
}

// Return the String time filename HHMMSS
String Datetime::toTimeFileName() {
  return time.toFileNameString();
}

// Return the String YYYY-MM-DD,HH:MM:SS
String Datetime::toLogString() {
  String log_string = "";
  log_string.concat(date.toLogString());
  log_string.concat(",");
  log_string.concat(time.toLogString());
  return log_string;
}

// Return the String YYYY-MM-DD+HH\%3AMM\%3ASS
String Datetime::toUploadString() {
  String datetime_string = "";
  datetime_string.concat("datetime=");
  datetime_string.concat(date.toUploadString());
  datetime_string.concat("+");
  datetime_string.concat(time.toUploadString());
  return datetime_string;
}
