#include "dto.h"
#include "SD.h"
#include "FS.h"
#include "SPI.h"
#include "HTTPClient.h"
#include "WiFi.h"

// WiFi Connection Settings
const char* SSID = "FBI van 2";
const char* PASS = "2059030897";

void setup() {
  delay(1000);  // UNIX
  Serial.begin(115200);  // Debugging

  StartWiFi();

  // Print formatted date.
  const Date date = {2020, 2, 23};
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
  const Location location = {33.500291, -89.75029};
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
  // SD Breakout Board Connections
  // | VCC | 3V3    |
  // | CS  | GPIO5  |
  // | DI  | GPIO23 |
  // | SCK | GPIO18 |
  // | DO  | GPIO19 |
  // | CD  | GND    |
  // | GND | GND    |
  if (SD.begin()) {
    Serial.println("Card mounted");
  } else {
    Serial.println("Failed to mount card");
  }

  // Test uploading two separate date points.
  char impact_buffer[512];
  Date impact_date = {2020, 2, 28};
  Time impact_time = {9, 27, 57};
  Datetime impact_datetime = {impact_date, impact_time};
  Location impact_location = {32.829121, -84.792222};
  Impact impact_upload = {impact_datetime, impact_location, true};
  FormattedImpact(impact_upload, impact_buffer);
  char travel_buffer[512];
  Date travel_date = {2020, 2, 21};
  Time travel_time = {9, 13, 47};
  Datetime travel_datetime = {travel_date, travel_time};
  Location travel_location = {35.72100, -86.0101};
  Travel travel_upload = {travel_datetime, travel_location, false};
  FormattedTravel(travel_upload, travel_buffer);

  // Write the impact string to the SD card
  //LogWrite(SD, "/20200225.log", formatted_impact_string);
  //LogWrite(SD, "/20200225.log", impact_buffer);
  LogWrite(SD, "/20200225.log", travel_buffer);
  LogRead(SD, "/20200225.log");
}

void loop() {
}

void FormatImpactUpload(const Impact& impact, char* out) {
  sprintf(out, "datetime=%4d-%02d-%02d+%02d\\%%3A%02d\\%%3A%02d&latitude=%0.6lf&longitude=%0.6lf&is-pothole=1",
          impact.datetime.date.year, impact.datetime.date.month, impact.datetime.date.day,
          impact.datetime.time.hour, impact.datetime.time.minute, impact.datetime.time.second,
          impact.location.latitude, impact.location.longitude);
}

void FormatTravelUpload(const Travel& travel, char* out) {
  sprintf(out, "datetime=%4d-%02d-%02d+%02d\\%%3A%02d\\%%3A%02d&latitude=%0.6lf&longitude=%0.6lf&is-pothole=0",
          travel.datetime.date.year, travel.datetime.date.month, travel.datetime.date.day,
          travel.datetime.time.hour, travel.datetime.time.minute, travel.datetime.time.second,
          travel.location.latitude, travel.location.longitude);
}

void LogUpload(const char* post) {
  //String postData = "datetime=2020-02-22+12\%3A45\%3A13&latitude=16.1453&longitude=15.231&is-pothole=1";
  //Serial.println(postData);

  HTTPClient http;
  http.begin("http://roadreporter.us/test/eventlog/postdemo.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  const int httpCode = http.POST(post); // send request
  String payload = http.getString(); // get response

  Serial.println(httpCode);
  Serial.println(payload);

  http.end();
}

void LogRead(fs::FS &fs, const char* path) {
  const bool file_exists = fs.exists(path);
  if (file_exists) {
    File log_file = fs.open(path);
    while(log_file.available()) {

      // Read the file for a string until we reach a newline character.
      String log_string = log_file.readStringUntil('\n');
      Serial.println();
      Serial.print("Uploading: ");
      Serial.println(log_string);

      // Parse the returned string for relevant values.
      Serial.println("Parsing Log...");
      uint16_t year = log_string.substring(0, 4).toInt();
      uint8_t month = log_string.substring(5, 7).toInt();
      uint8_t day = log_string.substring(8, 10).toInt();
      uint8_t hour = log_string.substring(11, 13).toInt();
      uint8_t minute = log_string.substring(14, 16).toInt();
      uint8_t second = log_string.substring(17, 19).toInt();
      float latitude = log_string.substring(20, 29).toFloat();
      float longitude = log_string.substring(30, 40).toFloat();
      bool is_pothole = log_string.substring(41, 42).toInt();

      // Debugging
      Serial.println("Results:");
      Serial.printf("Year: %d\n", year);
      Serial.printf("Month: %d\n", month); 
      Serial.printf("Day: %d\n", day); 
      Serial.printf("Hour: %d\n", hour); 
      Serial.printf("Minute: %d\n", minute); 
      Serial.printf("Second: %d\n", second); 
      Serial.printf("Latitude: %0.6lf\n", latitude);
      Serial.printf("Longitude: %0.6lf\n", longitude);
      Serial.printf("isPothole: %d\n", is_pothole);

      // Build data transfer structure.
      char post[512];
      Date date = {year, month, day};
      Time time = {hour, minute, second};
      Datetime datetime = {date, time};
      Location location = {latitude, longitude};

      // Upload impact if is_pothole is true, otherwise upload travel.
      if (is_pothole) {

        const Impact impact = {datetime, location, is_pothole};
        FormatImpactUpload(impact, post);
        Serial.println("Uploading impact log...");
        Serial.println(post);
        LogUpload(post);
        Serial.println("Upload complete!");
        delay(1000);  // Don't hit the website too much...
      } else {
        const Travel travel = {datetime, location, is_pothole};
        FormatTravelUpload(travel, post);
        Serial.println("Uploading travel log...");
        Serial.println(post);
        LogUpload(post);
        Serial.println("Upload complete!");
        delay(1000);  // Don't hit the website too much...
      }
    }  // end while
    log_file.close();  // Don't forget to close the file.
  }  // end if
}  // end LogRead()

void LogWrite(fs::FS &fs, const char* path, char* message) {
  const bool file_exists = fs.exists(path);
  if (file_exists) {
    File log_file = fs.open(path, FILE_APPEND);
    log_file.printf("%s\n", message);
    log_file.close();
  } else {
    File log_file = fs.open(path, FILE_WRITE);
    log_file.printf("%s\n", message);
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

void StartWiFi() {
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");
}