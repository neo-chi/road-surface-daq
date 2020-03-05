#include "dto.h"

// Test Date Construction
const uint16_t year = 2020;
const uint8_t month = 3;
const uint8_t day = 3;
Date date = {year, month, day};

// Test Time Construction
const uint8_t hour = 12;
const uint8_t minute = 8;
const uint8_t second = 19;
Time _time = {hour, minute, second};

// Test Datetime
Datetime datetime = {date, _time};

// Test Impact

// Test Travel

// Test Acceleration

// Test Environment

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  // Display date
  Serial.println("TEST: \t\t\t date.toString()");
  Serial.println("EXPECTED: \t 20200303");
  Serial.print("ACTUAL: \t\t ");
  Serial.println(date.toString());
  Serial.println();

  // Display time
  Serial.println("TEST: \t\t\t time.toString()");
  Serial.println("EXPECTED: \t 120819");
  Serial.print("ACTUAL: \t\t ");
  Serial.println(_time.toString());
  Serial.println();

  // Display datetime
  Serial.println("TEST: \t\t\t datetime.toString()");
  Serial.println("EXPECTED: \t 20200303,120819");
  Serial.print("ACTUAL: \t\t ");
  Serial.println(datetime.toString());
  Serial.println();
}

void loop() {

}
