#include "environment.h"

// The environment class is resopnsible for storing data colleced by the
// environmental sensor. Logging and uploading environmental data is made
// easier with the toLogString() and toUploadString() methods.
// toLogString(): returns the String "temperature,humidity,pressure,altitude"
// toUploadString(): returns the String
//   "temperature=TEMPERATURE&humidity=HUMIDITY&pressure=PRESSURE&altitude=ALTITUDE"
Environment::Environment(const float _temperature,
    const float _humidity,
    const float _pressure,
    const float _altitude) :
    temperature(_temperature),
    humidity(_humidity),
    pressure(_pressure),
    altitude(_altitude) {
  // Nothing to do here.
}

// Returns the String "temperature,humidity,pressure,altitude"
String Environment::toLogString() {
  String log = "";
  char formatted_environment[80];
  sprintf(formatted_environment, "%0.6lf,%0.6lf,%0.6lf,%0.6lf",
          temperature, humidity, pressure, altitude);
  log.concat(formatted_environment);
  return log;
}

// toUploadString(): returns the String
//   "temperature=TEMPERATURE&humidity=HUMIDITY&pressure=PRESSURE&altitude=ALTITUDE"
String Environment::toUploadString() {
  String log = "";
  char formatted_environment[80];
  sprintf(formatted_environment,
          "temperature=%0.6lf&humidity=%0.6lf&pressure=%0.6lf&altitude=%0.6lf",
          temperature, humidity, pressure, altitude);
  log.concat(formatted_environment);
  return log;
}
