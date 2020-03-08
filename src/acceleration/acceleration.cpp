#include "acceleration.h"

// The Acceleration class stores accelerometer x, y, and z axis data.
//
// If data for a given axis is not recorded, the value is replaced with a
// constant NOT_RECORDED defined as -100. When printing a string, the
// values not recorded will be displayed as NULL.
Acceleration::Acceleration(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {
  // Nothing to do here.
}

// Return the String "{acceleration.x},{acceleration.y},{acceleration.z}";
String Acceleration::toLogString() {
  String log = "";
  char format[80];
  sprintf(format, "%0.6lf,%0.6lf,%0.6lf", x, y, z);
  log.concat(format);
  return log;
}

// Returns the String "acceleration-x={X}&acceleratio-y={Y}&accelerationz={Z}"
String Acceleration::toUploadString() {
  String upload = "";
  char format[80];
  sprintf(format,
          "acceleration-x=%0.6lf&acceleration-y=%0.6lf&acceleration-z=%0.6lf",
          x, y, z);
  upload.concat(format);
  return upload;
}
