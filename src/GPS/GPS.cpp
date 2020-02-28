#include "GPS.h"

// GPS extends the SFE_UBLOX_GPS class and provides support for data transfer
// objects used in this project.
GPS::GPS() { };

Date GPS::getDate() {
  const uint16_t year = getYear();
  const uint8_t month = getMonth();
  const uint8_t day = getDay();
  const Date date{year, month, day};
  return date;
}

Time GPS::getTime() {
  const uint8_t hour = getHour();
  const uint8_t minute = getMinute();
  const uint8_t second = getSecond();
  const Time time{hour, minute, second};
  return time;
}

Datetime GPS::getDatetime() {
  const Date date = getDate();
  const Time time = getTime();
  const Datetime datetime = {date, time};
  return datetime;
}

Location GPS::getLocation() {
  const int ktogooglemaps = 10000000;
  const float latitude = (float)getLatitude() / ktogooglemaps;
  const float longitude = (float)getLongitude() / ktogooglemaps;
  const Location location{latitude, longitude};
  return location;
}

bool GPS::isConnected() {
  const uint8_t countSatellites = getSIV();
  if (countSatellites >= 3) {  // 3 satellites needed for triangulation.
    return true;
  } else {
    return false;
  }
}

void GPS::waitForConnection(/* const long timeout_millis = 0 */) {
  long elapsed_time = 0;
  bool timeout_enabled = false;
  bool timeout = false;
  long timeout_millis = 0;

  // Check if the user wishes to timeout after a given time.
  if (timeout_millis > 0) {
    timeout_enabled = true;
  } else {
    timeout_enabled = false;
  }

  // Wait until 3 satellites are connected. Return early if we time out.
  Serial.print("Connecting GPS to satellites");
  if (timeout_enabled) {
    while (!isConnected() && !timeout) {
      elapsed_time = millis();  // How many milliseconds have elapsed?
      timeout = elapsed_time > timeout_millis;
      Serial.print(".");  // wait for connection...
    }
  } else {
    while (!isConnected()) {
      Serial.print(".");  // wait for connection...
    }
  }

  // Sample GPS for a while to establish a strong connection.
  elapsed_time = millis();  // refresh elapsed_time to 0.
  while (millis() - elapsed_time < 10000) { 
    // Continue to sample GPS, wait for strong connection.
  }
}
