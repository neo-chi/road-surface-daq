#include "dto.h"

// The date class stores a day, month, and year from the GPS.
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

// The time class stores the hour, minute, and second variables from the GPS.
// The time may be returned in various formats using the following methods:
//   toString()
//   toLogString()
//   toUploadString()
Time::Time(uint8_t _hour, uint8_t _minute, uint8_t _second) {
  hour = _hour;
  minute = _minute;
  second = _second;
}

// Return the string HHMMSS.
String Time::toString() {
  String time_string = "";
  char formatted_time[20];
  sprintf(formatted_time, "%02d%02d%02d", hour, minute, second);
  time_string.concat(formatted_time);
  return time_string;
}

// Return the string HH:MM:SS.
String Time::toLogString() {
  String time_string = "";
  char formatted_time[20];
  sprintf(formatted_time, "%02d:%02d:%02d", hour, minute, second);
  time_string.concat(formatted_time);
  return time_string;
}

// Return the String HH\%3AMM\%3ASS.
String Time::toUploadString() {
  String time_string = "";
  char formatted_time[20];
  sprintf(formatted_time, "%02d\\%%3A%02d\\%%3A%02d", hour, minute, second);
  time_string.concat(formatted_time);
  return time_string;
}

// The Datetime class contains a date and time object that may be accessed
// individually and have their logging and upload Strings obtained.
Datetime::Datetime(Date _date, Time _time) : date(_date), time_(_time) {
  date = _date;
  time_ = _time;
}

// Return the String YYYYMMDD,HHMMSS
String Datetime::toString() {
  String datetime_string = "";
  datetime_string.concat(date.toString());
  datetime_string.concat(",");
  datetime_string.concat(time_.toString());
  return datetime_string;
}

// Return the String YYYY-MM-DD,HH:MM:SS
String Datetime::toLogString() {
  String date_string = date.toLogString();
  String time_string = time_.toLogString();
  String log_string = "";
  log_string.concat(date_string);
  log_string.concat(",");
  log_string.concat(time_string);
  return log_string;
}

// Return the String YYYY-MM-DD+HH\%3AMM\%3ASS
String Datetime::toUploadString() {
  String datetime_string = "datetime=";
  datetime_string.concat(date.toUploadString());
  datetime_string.concat("+");
  datetime_string.concat(time_.toUploadString());
  return datetime_string;
}


