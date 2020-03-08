#include "date.h"

// The date class stores a day, month, and year from the GPS.
// The date may be used to create a filename or a log string.
//   Date.toFileNameString(): returns the String YYYYMMDD
//   Date.toLogString(): returns the String YYYY-MM-DD
Date::Date(uint16_t _year, uint8_t _month, uint8_t _day)
            : year(_year), month(_month), day(_day) {
  // Nothing to do here.
}

// Return the String YYYYMMDD
String Date::toFileNameString() {
  const uint8_t kSizeOfDate = 80;
  char formatted_date[kSizeOfDate];
  sprintf(formatted_date, "%04d%02d%02d", year, month, day);
  String return_string = "";
  return_string.concat(formatted_date);
  return return_string;
}

// Return the String YYYY-MM-DD
String Date::toLogString() {
  const uint8_t kSizeOfDate = 80;
  char formatted_date[kSizeOfDate];
  sprintf(formatted_date, "%04d-%02d-%02d", year, month, day);
  String return_string = "";
  return_string.concat(formatted_date);
  return return_string;
}

// Return the string YYYY-MM-DD
String Date::toUploadString() {
  return toLogString();
}