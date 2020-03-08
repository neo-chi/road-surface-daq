#include "environment.h"
#include "rtest.h"

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  const float temperature = 1.1;
  const float humiditiy = 2.22;
  const float pressure = 3.333;
  const float altitude = 4.4444;
  Environment environment{temperature, humiditiy, pressure, altitude};

  StringTest toLogString{
    "Environment.toLogString()",
    "1.100000,2.220000,3.333000,4.444400",
    environment.toLogString()
  };
  toLogString.Execute();

  StringTest toUploadString{
    "Environment.toUploadString()",
    "temperature=1.100000&humidity=2.220000&pressure=3.333000&altitude=4.444400",
    environment.toUploadString()
  };
  toUploadString.Execute();

}

void loop() {
  // Nothing to do here.
}