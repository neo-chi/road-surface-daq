#include "dto.h"

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  // Print the formatted date.
  const Date date = {2020, 2, 27};
  char formatted_date_string[80];
  Serial.println("Formatting date...");
  FormattedDate(date, formatted_date_string);
  Serial.println("Date formatted...");
  Serial.println("Printing formatted date..");
  Serial.println(formatted_date_string);
  Serial.println("Formatted date print success!");
}

void loop() {

}

void FormattedDate(const Date date, char* out) {
  sprintf(out, "%04d-%02d-%02d", date.year, date.month, date.day);
}