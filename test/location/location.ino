#include "location.h"
#include "rtest.h"

void setup() {

  // Setup
  const float LATITUDE = 35.0687;
  const float LONGITUDE = -83.229100;
  Location location{LATITUDE, LONGITUDE};

  StringTest test_toLogString{
    "Location.toLogString()",
    "35.068699,-83.229099",
    location.toLogString()
    };
  test_toLogString.Execute();

  StringTest test_toUploadString{
    "Location.toUploadString()",
    "latitude=35.068699&longitude=-83.229099",
    location.toUploadString()
    };
  test_toUploadString.Execute();

}

void loop() {
  // Nothing to do here.
}