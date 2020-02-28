#include <Wire.h>
//#include "SparkFun_Ublox_Arduino_Library.h"
#include "GPS.h"
#include "SD.h"
#include "FS.h"
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
#include <LIS3DH.h>
#include "SPI.h"
#include "HTTPClient.h"
#include "WiFi.h"
#include "dto.h"

#define SEALEVELPRESSURE_HPA (1013.25)

#define TEMP_CFG_REG_CONFIGURATION  0x80
#define CTRL_REG1_CONFIGURATION     0x97
#define CTRL_REG2_CONFIGURATION     0x00
#define CTRL_REG3_CONFIGURATION     0x40
#define CTRL_REG4_CONFIGURATION     0x08
#define CTRL_REG5_CONFIGURATION     0x88
#define CTRL_REG6_CONFIGURATION     0x00
#define STATUS_REG_CONFIGURATION    0x00
#define FIFO_CTRL_REG_CONFIGURATION 0x00
#define FIFO_SRC_REG_CONFIGURATION  0x00
#define INT1_CFG_CONFIGURATION      0x20
#define INT1_SRC_CONFIGURATION      0x00
#define INT1_THS_CONFIGURATION      0xFF
#define INT1_DURATION_CONFIGURATION 0x00
#define CLICK_CFG_CONFIGURATION     0x00
#define CLICK_SRC_CONFIGURATION     0x00
#define CLICK_THS_CONFIGURATION     0x00
#define TIME_LIMIT_CONFIGURATION    0x00
#define TIME_LATENCY_CONFIGURATION  0x00
#define TIME_WINDOW_CONFIGURATION   0x00


// GPS constructor
GPS gps;

// Accelerometer construction
LIS3DH accelerometer;
struct Accel {
  const uint8_t PIN;
  volatile bool isPothole;  // MAKE THIS VALUE VOLATILE -- LIABLE TO CHANGE AT ANY TIME BY INTERRUPT. -- Reece
};
Accel z_axis = {16, false};


// Accelerometer ISR
volatile bool interrupt_triggered = false;
void IRAM_ATTR ISR() {
  interrupt_triggered = true;
  z_axis.isPothole = true;
  Serial.println("INTERRUPT TRIGGERED");
  //accelerometer.configurationRead(INT1_SRC);
}

// WiFi connection information (private)
const char* SSID = "Samsung Galaxy Note8_9949";
const char* PASS = "whispersilk";

// Timer setup
long elapsed_time = 0;

void setup() {
  delay(1000); // UNIX

  Serial.begin(115200); // Open Serial monitor for debugging.

  // Configure acclerometer control registers.
    accelerometer.configurationWrite(CTRL_REG1,     CTRL_REG1_CONFIGURATION);
    accelerometer.configurationWrite(CTRL_REG2,     CTRL_REG2_CONFIGURATION);
    accelerometer.configurationWrite(CTRL_REG3,     CTRL_REG3_CONFIGURATION);
    accelerometer.configurationWrite(CTRL_REG4,     CTRL_REG4_CONFIGURATION);
    accelerometer.configurationWrite(CTRL_REG5,     CTRL_REG5_CONFIGURATION);
    //accelerometer.configurationWrite(CTRL_REG6,     CTRL_REG6_CONFIGURATION);
    //accelerometer.configurationWrite(STATUS_REG,    STATUS_REG_CONFIGURATION);
    accelerometer.configurationWrite(FIFO_CTRL_REG, FIFO_CTRL_REG_CONFIGURATION);
    //accelerometer.configurationWrite(FIFO_SRC_REG,  FIFO_SRC_REG_CONFIGURATION);
    accelerometer.configurationWrite(INT1_CFG,      INT1_CFG_CONFIGURATION);
    accelerometer.configurationWrite(INT1_SRC,      INT1_SRC_CONFIGURATION);
    accelerometer.configurationWrite(INT1_THS,      INT1_THS_CONFIGURATION);
    accelerometer.configurationWrite(INT1_DURATION, INT1_DURATION_CONFIGURATION);
    accelerometer.configurationWrite(CLICK_CFG,     CLICK_CFG_CONFIGURATION);
    accelerometer.configurationWrite(CLICK_SRC,     CLICK_SRC_CONFIGURATION);
    accelerometer.configurationWrite(CLICK_THS,     CLICK_THS_CONFIGURATION);
    accelerometer.configurationWrite(TIME_LIMIT,    TIME_LIMIT_CONFIGURATION); 
    accelerometer.configurationWrite(TIME_LATENCY,  TIME_LATENCY_CONFIGURATION);
    accelerometer.configurationWrite(TIME_WINDOW,   TIME_WINDOW_CONFIGURATION); 

  // Attach interrupt to accelerometer z_axis
  pinMode(z_axis.PIN, INPUT);
  attachInterrupt(z_axis.PIN, ISR, HIGH);
  
  // Reset interrupt trigger.
  accelerometer.configurationRead(INT1_SRC);
  
  // If an SD card is mounted, establish communication with it.
  if (SD.begin()) {
    Serial.println("Card Mounted");
  } else {
    Serial.println("Card Mount Failed");
    return;
  }
  delay(2000); // Allow time to read SD card state...

  // Establish GPS module communication.
  Wire.begin();
  gps.begin();
  gps.setI2COutput(COM_TYPE_UBX);
  gps.saveConfiguration();
  gps.setNavigationFrequency(3); // set GPS update rate to 3Hz

} // end setup

long upload_elapsed_time = 0;
char buffer[512];
const char* PATH = "/20200228.log";

void loop() {

  // Unlatch the interrupt trigger.
  if (interrupt_triggered) {
    interrupt_triggered = false;
    Serial.println("Interrupt Triggered");
    accelerometer.configurationRead(INT1_SRC); // Unlatch the interrupt.
    Serial.println("Interrupt Latch Released");
    const Datetime datetime{gps.getDatetime()};
    const Location location{gps.getLocation()};
    const Impact impact{datetime, location, true};
    FormattedImpact(impact, buffer);
    Serial.println();
    Serial.printf("%s\n", buffer);
    Serial.println();
    LogWrite(SD, PATH, buffer);
    delay(1000); // Wait a moment to allow file to close.
    Serial.println("Interrupt Complete");
    Serial.flush();
  }

  // Test waiting for GPS connection.
  if (!gps.isConnected()) {
    gps.waitForConnection();
    delay(10000);
  }

  // Wait 2 seconds before polling GPS again.
  if (millis() - elapsed_time > 2000) {

    // Construct a Location object with GPS
    Serial.println();
    Serial.println("Getting GPS location...");
    const Location _location{gps.getLocation()};
    Serial.printf("Location: %0.6lf,%0.6lf\n", _location.latitude, _location.longitude);
    Serial.println();

    // Record Travel...
    const Datetime datetime{gps.getDatetime()};
    const Location location{gps.getLocation()};
    const Travel travel{datetime, location, false};
    FormattedTravel(travel, buffer);
    LogWrite(SD, PATH, buffer);  // Write the data to the log

    // Get GPS speed for state change
    const int32_t speed = gps.getGroundSpeed();
    Serial.printf("Ground Speed: %d\n", speed);
    if (speed < 1000) {
      Serial.println("STATE(IDLE)");
    } else {
      Serial.println("STATE(MOVING)");
    }

    elapsed_time = millis();  // update time.
  }

  // Upload data...
  if (millis() - upload_elapsed_time > 60000) {
    Serial.println("Uploading Logs...");
    delay(5000);
    StartWiFi();
    if (WiFi.status() == WL_CONNECTED) {
      LogRead(SD, PATH); // Upload data to database.
    }
    WiFi.mode(WIFI_OFF);
    upload_elapsed_time = millis();
  }

  // Read and display accelerometer data.
  accelerometer.read();
  Serial.print(accelerometer.x_g);
  Serial.print("\t");
  Serial.print(accelerometer.y_g);
  Serial.print("\t");
  Serial.println(accelerometer.z_g);

} // end loop

/*!
   @brief Given the date time, sample GPS and write data to file.
   @param uint16_t year
   @param uint16_t month
   @param uint16_t day
*/
void writeLogFile(fs::FS &fs, uint16_t year, uint8_t month, uint8_t day) {

  // Generate filename.
  char PATH[79];
  sprintf(PATH, "/%d%02X%02X.log", year, month, day); // PATH = datetime

  // If file exists, append data.
  if (fs.exists(PATH)) {

    // Collect GPS data to be logged..
    const long                                          TO_GOOGLE_MAPS = 10000000;
    const float latitude  = (float)gps.getLatitude()  / TO_GOOGLE_MAPS;
    const float longitude = (float)gps.getLongitude() / TO_GOOGLE_MAPS;
    const float year      =        gps.getYear();
    const float month     =        gps.getMonth();
    const float Day       =        gps.getDay();
    const float hour      =        gps.getHour();
    const float minute    =        gps.getMinute();
    const float second    =        gps.getSecond();
    //TODO: bool isPothole = true;

    // Append data to file.
    File file = fs.open(PATH, "a"); file.printf("%0.6lf,%0.6lf,%0.6lf,%0.6lf,%0.6lf,%0.6lf\r\n", year, month, day, hour, minute, second);
    file.printf("%0.6lf\r\n", latitude);
    file.printf("%0.6lf\r\n", longitude);
    // TODO: file.printf(isPothole);

    // If file does not exists, write a new file and add data.
  } else {

    // Collect GPS data to be logged..
    const long                                          TO_GOOGLE_MAPS = 10000000;
    const float latitude  = (float)gps.getLatitude()  / TO_GOOGLE_MAPS;
    const float longitude = (float)gps.getLongitude() / TO_GOOGLE_MAPS;
    const float year      =        gps.getYear();
    const float month     =        gps.getMonth();
    const float Day       =        gps.getDay();
    const float hour      =        gps.getHour();
    const float minute    =        gps.getMinute();
    const float second    =        gps.getSecond();

    // Write data to file.
    File file = fs.open(PATH, "w");
    file.printf("%0.6lf,%0.6lf,%0.6lf,%0.6lf,%0.6lf,%0.6lf\r\n", year, month, day, hour, minute, second);
    file.printf("%0.6lf\r\n", latitude);
    file.printf("%0.6lf\r\n", longitude);

   //////////////////////////////////////////////////////////////////////////////// 
   //////////////////////////////////////////////////////////////////////////////// 
   //////////////////////////////////////////////////////////////////////////////// 
   // our ground speed is less than 1000, upload data.
   // otherwise, keep gathering data.
   

  }

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