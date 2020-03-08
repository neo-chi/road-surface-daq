#include "travel.h"

// The Travel class stores data about vehicle movement where impacts are not
// detected. It provides the following functions for logging and uploading:
// String toLogString(): return a String for logging to a file.
// String toUploadString(): return a String for uploading to a database.
Travel::Travel(Datetime _datetime, Location _location)
             : datetime(_datetime), location(_location) {
  // Nothing else to do here.
}

// Return the String YYYY-MM-DD,HH-MM-SS
String Travel::toLogString() {
  String return_string = "";
  return_string.concat(datetime.toLogString());
  return_string.concat(",");
  return_string.concat(location.toLogString());
  return return_string;
}

// Return the String YYYY-MM-DD,HH-MM-SS,{latituce},{longitude}
String Travel::toUploadString() {
  String return_string = "";
  return_string.concat(datetime.toUploadString());
  return_string.concat("&");
  return_string.concat(location.toUploadString());
  return return_string;
}
