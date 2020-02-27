#include "dto.h"

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  // Print formatted date.
  const Date date = {2020, 2, 27};
  char formatted_date_string[80];
  Serial.println("Formatting date...");
  FormattedDate(date, formatted_date_string);
  Serial.println("Date formatted...");
  Serial.println("Printing formatted date..");
  Serial.println(formatted_date_string);
  Serial.println("Formatted date print success!");
  Serial.println();

  // Print formatted time.
  const Time time = {13, 4, 17};
  char formatted_time_string[80];
  Serial.println("Formatting time...");
  FormattedTime(time, formatted_time_string);
  Serial.println("Date formatted...");
  Serial.println("Printing formatted time..");
  Serial.println(formatted_time_string);
  Serial.println("Formatted time print success!");
  Serial.println();

  // Print formatted datetime.
  const Datetime datetime = {date, time};
  char formatted_datetime_string[80];
  Serial.println("Formatting datetime...");
  FormattedDatetime(datetime, formatted_datetime_string);
  Serial.println("Datetime formatted...");
  Serial.println("Printing formatted datetime..");
  Serial.println(formatted_datetime_string);
  Serial.println("Formatted datetime print success!");
  Serial.println();

   // Print formatted location.
  const Location location = {33.500291, -86.75029};
  char formatted_location_string[80];
  Serial.println("Formatting location...");
  FormattedLocation(location, formatted_location_string);
  Serial.println("Location formatted...");
  Serial.println("Printing formatted location..");
  Serial.println(formatted_location_string);
  Serial.println("Formatted location print success!");
  Serial.println();

  // Print formatted impact.
  Impact impact = {datetime, location , true};
  char formatted_impact_string[80];
  Serial.println("Formatting impact...");
  FormattedImpact(impact, formatted_impact_string);
  Serial.println("Impact formatted...");
  Serial.println("Printing formatted impact..");
  Serial.println(formatted_impact_string);
  Serial.println("Formatted impact print success!");
  Serial.println();

  // Print formatted travel.
  Impact travel = {datetime, location , false};
  char formatted_travel_string[80];
  Serial.println("Formatting travel...");
  FormattedImpact(travel, formatted_travel_string);
  Serial.println("Impact formatted...");
  Serial.println("Printing formatted travel..");
  Serial.println(formatted_travel_string);
  Serial.println("Formatted travel print success!");
  Serial.println();
}

void loop() {

}

int bytes_added(int result_of_sprintf) {
  if (result_of_sprintf > 0) {
    return result_of_sprintf;
  } else {
    return 0;
  }
}

int FormattedTravel(const Travel& travel, char* out) {
  int length = 0;
  length += FormattedDatetime(travel.datetime, out + length);
  length += bytes_added(sprintf(out + length, ","));
  length += FormattedLocation(travel.location, out + length);
  length += bytes_added(sprintf(out + length, ",%d", travel.is_pothole));
  return length;
}

int FormattedImpact(const Impact& impact, char* out) {
  int length = 0;
  length += FormattedDatetime(impact.datetime, out + length);
  length += bytes_added(sprintf(out + length, ","));
  length += FormattedLocation(impact.location, out + length);
  length += bytes_added(sprintf(out + length, ",%d", impact.is_pothole));
  return length;
}

int FormattedLocation(const Location& location, char* out) {
  const int bytes_added = sprintf(out, "%0.6lf,%0.6lf", location.latitude, location.longitude);
  return bytes_added;
}

int FormattedDatetime(const Datetime& datetime, char* out) {
  const int bytes_added = sprintf(out, "%04d-%02d-%02d %02d:%02d:%02d", datetime.date.year,
                                                                        datetime.date.month,
                                                                        datetime.date.day,
                                                                        datetime.time.hour,
                                                                        datetime.time.minute,
                                                                        datetime.time.second);
  return bytes_added;
}

int FormattedDate(const Date& date, char* out) {
  const int bytes_added = sprintf(out, "%04d-%02d-%02d", date.year, date.month, date.day);
  return bytes_added;
}

int FormattedTime(const Time& time, char* out) {
  const int bytes_added = sprintf(out, "%02d:%02d:%02d", time.hour, time.minute, time.second);
  return bytes_added;
}