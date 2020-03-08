#include "location.h"

// The Location class stores GPS latitude and longitude information for ease
// of use when logging to a file and uploading to a datebase.
// String toLogString(): returns the String LATITUDE,LONGITUDE
Location::Location(const float _latitude, const float _longitude)
              : latitude(_latitude), longitude(_longitude) {
  // Nothing to do here.
}

// Returns the String LATITUDE,LONGITUDE
String Location::toLogString() {
  String return_string = "";
  char formatted_location[20];
  sprintf(formatted_location,
      "%0.6lf,%0.6lf",
      latitude, longitude);
  return_string.concat(formatted_location);
  return return_string;
}

// Returns the String latitude=LATITUDE&longitude=LONGITUDE
String Location::toUploadString() {
  String return_string = "";
  char formatted_location[80];
  sprintf(formatted_location,
      "latitude=%0.6lf&longitude=%0.6lf",
      latitude, longitude);
  return return_string;
}
