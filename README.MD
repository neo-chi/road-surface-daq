# Road Surface Data Acquistion System

## TODO

### Data Transfer Objects

- [x] Implement Date
- [x] Implement Time
- [x] Implement Datetime
- [x] Implement Acceleration
- [x] Implement Impact
  - [ ] Refactor Impact to accept an enum for impact-severity
- [x] Implement Travel
- [x] Implement Environment

### Actions

- [x] Test DataCollector
- [x] Test Storage
- [] Test DataCollector -> Storage mediation
- [] Test Uploader
- [] Test Stroage -> Uploader mediation

## Table of Contents

## Log File Format

### Impact

Impact data is collected when the vehicle has a high vertical response, likely
due to something with the road. In this event, the location is tagged with the
date, time, location, vehicle speed, and environmental conditions. After this,
acceleration data is recorded. This allows for the identification of the
severity of the damage to the road.

**Filename:** HHMMSS.imp

**Content:**

DATETIME,LOCATION,SPEED,ENVIRONMENT **\n** <br>
ACCELERATION_X,ACCLERATION_Y,ACCELERATION_Z **\n** <br>
ACCELERATION_X,ACCLERATION_Y,ACCELERATION_Z **\n** <br>
ACCELERATION_X,ACCLERATION_Y,ACCELERATION_Z **\n** <br>

...

**EOF**

### Impact (GPS not connected)

In the event that the GPS cannot recieve satellite communication, it is still
important to gather information about road surface quality for analysis. For
this reason, an impact will cause acceleration data to be written to a file
without the date, time, location, or environmental data tagged.

**Filename:** NC_{XXXXX}.imp

**Content:**

ACCELERATION_X,ACCLERATION_Y,ACCELERATION_Z **\n** <br>
ACCELERATION_X,ACCLERATION_Y,ACCELERATION_Z **\n** <br>
ACCELERATION_X,ACCLERATION_Y,ACCELERATION_Z **\n** <br>

...

**EOF**

### Travel

Travel data records the path the vehicle drives. By exclusion of events,
it may be determined that travel data points without overlapping impact data
points are quality roads, without severe damage to its surface.

**Filename:** HHMMSS.trv

**Content:**

DATETIME,LOCATION,SPEED **\n** <br>
DATETIME,LOCATION,SPEED **\n** <br>
DATETIME,LOCATION,SPEED **\n** <br>

...

**EOF**

### Environment

Given that environmental conditions have little variance with distance,
environmental data will be collected only every 30 minutes. Environmental data
may be correlated with road surface deterioration rate with respect to time.

**Filename:** YYYYMMDD.env

**Content:**

DATETIME,LOCATION,ENVIORNMENT **\n** <br>
DATETIME,LOCATION,ENVIORNMENT **\n** <br>
DATETIME,LOCATION,ENVIORNMENT **\n** <br>

...

**EOF**

## Hardware

The hardware implemented in this system is relatively inexpensive. Traditional
designs include powerful sensors attached to specially-designed vehciles. The
system remains inexpensive with the use of consumer-electronics and automatic
post-processing of collected data.

### Subsystem 1

Subsystem 1 is responsible for the primary actions of this system, including
primary data collection, data logging, and data uploading.

* ESP32-WROOM-32D DevkitC-V4
* Adafruit LIS3DH 3-Axis Digital Accelerometer
* Sparkfun ZOE-M8Q GPS
* Sparkfun Level Shifting Micro SD Card Breakout Board
* BME280 Environmental Sensor
* 32 GB Micro SD Card

### Subsystem 2

Subsystem 2 is responsible for capturing images of impact events.
Responsibilities of this subsystem may increase in the future, given
the hardware capabilities of the Raspberry Pi Zero W.

* Raspberry Pi Zero W
* Raspberry Pi Camera V2
* 32 GB Micro SD Card

### Connections

The ESP32-WROOM-32D serves as the primary microcontroller of this system.
Thus, it suppports the most connections to sensors.
* The I2C interfaces with the LIS3DH accelerometer, GPS, and environmental
sensor.
* The SPI interfaces with the SD card.

| ESP32-WROOM-32D | LIS3DH | GPS | SD Card | Environmental |
| --------------- | ------ | --- | ------- | ------------- |
| --------------- | ------ | --- | ------- | ------------- |
| --------------- | ------ | --- | ------- | ------------- |
| --------------- | ------ | --- | ------- | ------------- |
| --------------- | ------ | --- | ------- | ------------- |
| --------------- | ------ | --- | ------- | ------------- |
| --------------- | ------ | --- | ------- | ------------- |
| --------------- | ------ | --- | ------- | ------------- |
