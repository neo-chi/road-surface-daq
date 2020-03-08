#include "acceleration.h"
#include "rtest.h"

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  const float x = 1.111;
  const float y = 2.222;
  const float z = 3.333;
  Acceleration acceleration{x, y, z};

  StringTest TEST_toLogString{
    "Acceleration.toLogString()",
    "1.111000,2.222000,3.333000",
    acceleration.toLogString()
  };
  TEST_toLogString.Execute();

  StringTest TEST_toUploadString{
    "Acceleration.toUploadString()",
    "acceleration-x=1.111000&acceleration-y=2.222000&acceleration-z=3.333000",
    acceleration.toUploadString()
  };
  TEST_toUploadString.Execute();

}

void loop() {
  // Nothing to do here.
}