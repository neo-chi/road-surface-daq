// This file tests the individual capabilites of the GPS library.
#include "GPS.h"
#include "Wire.h"

GPS gps;

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging.

  // Initialize GPS
  Wire.begin();
  gps.begin();
  gps.setI2COutput(COM_TYPE_UBX);
  gps.saveConfiguration();

}

long elapsed_time = 0;
void loop() {
  // Test waiting for GPS connection.
  if (!gps.isConnected()) {
    Serial.print("GPS connecting to satellites");
    gps.waitForConnection();
  }

  Serial.println();

  // Construct a date object with GPS.
  Serial.println("Getting GPS date...");
  const Date date{gps.getDate()};
  Serial.printf("Date: %04d,%02d,%02d\n", date.year, date.month, date.day);

  // Construct a time object with GPS.
  Serial.println("Getting GPS time...");
  const Time time{gps.getTime()};
  Serial.printf("Time: %02d,%02d,%02d\n", time.hour, time.minute, time.second);

  // Construct a datetime object with GPS;
  Serial.println();
  Serial.println("Getting GPS datetime...");
  const Datetime datetime{gps.getDatetime()};
  Serial.printf("Datetime: %04d,%02d,%02d,%02d,%02d,%02d\n",
      datetime.date.year, datetime.date.month, datetime.date.day,
      datetime.time.hour, datetime.time.minute, datetime.time.second);

  // Wait 2 seconds before polling GPS again.
  if (millis() - elapsed_time > 2000) {
    elapsed_time = millis();  // update time.

    // Construct a Location object with GPS
    Serial.println("Getting GPS location...");
    const Location location{gps.getLocation()};
    Serial.printf("Location: %0.6lf,%0.6lf\n", location.latitude, location.longitude);

    // Get GPS speed for state change
    const int32_t speed = gps.getGroundSpeed();
    Serial.printf("Ground Speed: %d\n", speed);
    if (speed < 1000) {
      Serial.println("STATE(IDLE): Connecting to WiFi and uploading...");
    } else {
      Serial.println("STATE(MOVING): Disconnecting WiFi and halting upload.");
    }
  }
}
