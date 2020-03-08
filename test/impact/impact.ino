#include "impact.h"
#include "rtest.h"

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  // Setup datetime
  const uint16_t year = 2020;
  const uint8_t month = 1;
  const uint8_t day = 6;
  Date date{year, month, day};
  const uint8_t hour = 3;
  const uint8_t minute = 29;
  const uint8_t second = 4;
  Time time{hour, minute, second};
  Datetime datetime{date, time};

  // Setup location
  const float latitude = 35.0687;
  const float longitude = -83.229100;
  Location location{latitude, longitude};

  // Setup Impact
  Impact impact{datetime, location};
  StringTest toLogString{
    "Impact.toLogString()",
    "2020-01-06,03:29:04,35.068699,-83.229103",
    impact.toLogString()
  };
  toLogString.Execute();

  StringTest toUploadString{
    "Impact.toUploadString()",
    "datetime=2020-01-06+03\\%3A29\\%3A04&latitude=35.068699&longitude=-83.229103&is-pothole=1",
    impact.toUploadString()
  };
  toUploadString.Execute();
}


void loop() {
  // Nothing to do here.
}