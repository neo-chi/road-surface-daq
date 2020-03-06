#include "dto.h"

// The date class stores a day, month, and year from the GPS.
Date::Date() {

}

Date::Date(uint16_t _year, uint8_t _month, uint8_t _day) {
  year = _year;
  month = _month;
  day = _day;
}

// Return the String YYYYMMDD.
String Date::toString() {
  const uint8_t kSizeOfDate = 80;
  char formatted_date[kSizeOfDate];
  sprintf(formatted_date, "%04d%02d%02d", year, month, day);
  String return_string = "";
  return_string.concat(formatted_date);
  return return_string;
}

// Return the String YYYY-MM-DD.
String Date::toLogString() {
  const uint8_t kSizeOfDate = 80;
  char formatted_date[kSizeOfDate];
  sprintf(formatted_date, "%04d-%02d-%02d", year, month, day);
  String return_string = "";
  return_string.concat(formatted_date);
  return return_string;
}

// Return the String YYYY-MM-DD.
String Date::toUploadString() {
  return toLogString();
}

Datetime::Datetime(Date _date, Time _time) : date(_date) {
  date = _date;
  time = _time;
}

String Datetime::toString() {
  return toLogString();
}

String Datetime::toLogString() {
  String date_string = date.toString();
  String time_string = time.toString();
  String log_string = "";
  log_string.concat(date_string);
  log_string.concat(",");
  log_string.concat(time_string);
  return log_string;
}

String Datetime::toUploadString() {
  // TODO
}


