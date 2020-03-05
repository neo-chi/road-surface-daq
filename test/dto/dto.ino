#include "dto.h"

// Test Date Construction
const uint16_t year = 2020;
const uint8_t month = 3;
const uint8_t day = 3;
Date date = {year, month, day};

// Test Time Construction

// Test Datetime

// Test Impact

// Test Travel

// Test Acceleration

// Test Environment

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  Serial.println(date.toString());
}

void loop() {

}
