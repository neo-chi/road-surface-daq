#include "Time.h"

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
String Time::toFileNameString() {
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
