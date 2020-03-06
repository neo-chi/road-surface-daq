#include "dto.h"

// The date class stores a day, month, and year from the GPS.
Date(uint16_t _year, uint16_t _month, uint16_t _day) {
  year = _year;
  month = _month;
  day = _day;
}

//Return the String YYYYMMDD.
String Date::toString() {
  const uint8_t kSizeOfDate = 12;
  char formatted_date[kSizeOfDate];
  sprintf(formatted_date, "%04d%02d%02d", year, month, day);
  String return_string = "";
  return_string.concat(formatted_date);
  return return_string;
}

// Return the String YYYY-MM-DD.
String Date::toLogString() {
  const uint8_t kSizeOfDate = 12;
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

