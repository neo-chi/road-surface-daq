#include "datetime.h"
#include "rtest.h"

void setup() {
  // Setup debugging in console
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  // Setup dateime
  const uint16_t year = 2020;
  const uint8_t month = 1;
  const uint8_t day = 6;
  Date date{year, month, day};
  const uint8_t hour = 3;
  const uint8_t minute = 29;
  const uint8_t second = 4;
  Time time{hour, minute, second};
  Datetime datetime{date, time};

  // Test toLogString() method
  StringTest toLogString{
    "Datetime.toLogString()",
    "2020-01-06,03:29:04",
    datetime.toLogString()
  };
  toLogString.Execute();

  // Test toUploadString() method
  StringTest toUploadString{
    "Datetime.toUploadString()",
    "datetime=2020-01-06+03\\%3A29\\%3A04",
    datetime.toUploadString()
  };
  toUploadString.Execute();
}

void loop() {

}