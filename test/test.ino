#include "dto.h"
#include "SD.h"
#include "FS.h"
#include "SPI.h"
#include "HTTPClient.h"

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
  Travel travel = {datetime, location , false};
  char formatted_travel_string[80];
  Serial.println("Formatting travel...");
  FormattedTravel(travel, formatted_travel_string);
  Serial.println("Impact formatted...");
  Serial.println("Printing formatted travel..");
  Serial.println(formatted_travel_string);
  Serial.println("Formatted travel print success!");
  Serial.println();

  // Print formatted Impact structure upload string.
  char post[512];
  FormatImpactUpload(impact, post);
  Serial.println("Formatting impact upload string...");
  Serial.println("Printing formatted impact upload string..");
  Serial.println(post);
  Serial.println();

  // Print formatted travel structure upload string.
  FormatTravelUpload(travel, post);
  Serial.println("Formatting travel upload string...");
  Serial.println("Printing formatted travel upload string..");
  Serial.println(post);
  Serial.println();

  // TODO: verify SD connection
  //delay(1000);
  //if (SD.begin()) {
    //Serial.println("Card mounted");
  //} else {
    //Serial.println("Failed to mount card");
  //}
  //delay(1000);

  //LogWrite(SD, "/log.poo", formatted_impact_string);
}

void loop() {
}

void FormatImpactUpload(const Impact& impact, char* out) {
  sprintf(out, "datetime=%4d-%02d-%02d+%02d\\%%3A%02d\\%%3A02d&latitude=%0.6lf&longitude=%0.6lf&is-pothole=1",
  impact.datetime.date.year, impact.datetime.date.month, impact.datetime.date.day,
  impact.datetime.time.hour, impact.datetime.time.minute, impact.datetime.time.second,
  impact.location.latitude, impact.location.longitude);
}

void FormatTravelUpload(const Travel& travel, char* out) {
  sprintf(out, "datetime=%4d-%02d-%02d+%02d\\%%3A%02d\\%%3A02d&latitude=%0.6lf&longitude=%0.6lf&is-pothole=0",
  travel.datetime.date.year, travel.datetime.date.month, travel.datetime.date.day,
  travel.datetime.time.hour, travel.datetime.time.minute, travel.datetime.time.second,
  travel.location.latitude, travel.location.longitude);
}

void LogUpload(const char* post) {
  String postData = "datetime=2020-02-22+12\%3A45\%3A13&latitude=16.1453&longitude=15.231&is-pothole=1";
  Serial.println(postData);

  HTTPClient http;
  http.begin("http://roadreporter.us/test/eventlog/postdemo.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  const int httpCode   = http.POST(postData); // send request
  String payload = http.getString(); // get response

  Serial.println(httpCode);
  Serial.println(payload);

  http.end();

  while(1) {
    delay(10000);
  }
}

void LogRead(fs::FS &fs, const char* path) {
  const bool file_exists = fs.exists(path);
  if (file_exists) {
    File log_file = fs.open(path);
    while(log_file.available()) {
      Serial.println(log_file.read());
    }
    log_file.close();
  }
}

void LogWrite(fs::FS &fs, const char* path, char* message) {
  const bool file_exists = fs.exists(path);
  if (file_exists) {
    File log_file = fs.open(path, FILE_APPEND);
    log_file.printf("%s", message);
    log_file.close();
  } else {
    File log_file = fs.open(path, FILE_WRITE);
    log_file.printf("%s", message);
    log_file.close();
  }
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