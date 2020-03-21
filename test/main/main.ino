/* FILE:        main.ino
 * AUTHOR:      Reece Chimento
 * DATE:        2020-03-XX
 * DESCRIPTION:
 */

// Devices
#include "accelerometer.h"
#include "environmental_sensor.h"
#include "gps.h"
#include "storage.h"
#include "wifi.h"

// Controllers
#include "impact_controller.h"
#include "travel_controller.h"

// Clarity functions
#define disable_interrupts() cli()
#define enable_interrupts()  sei()

// Clarity constants
#define SECOND                  1000
#define MINUTE                  60 * SECOND
#define HOUR                    60 * MINUTE
#define DAY                     24 * HOUR

// Update these to control functions.
#define ACCELERATION_BUF_LEN            512
#define GPS_CONNECT_TIMEOUT             10 * SECOND
#define WIFI_CONNECT_TIMEOUT            10 * SECOND
#define ENV_UPDATE_CACHE_TIME           10 * MINUTE
// [ ] Make update time depend on gps time
#define GPS_UPDATE_CACHE_YEAR_TIME      30 * MINUTE
#define GPS_UPDATE_CACHE_MONTH_TIME     30 * MINUTE
#define GPS_UPDATE_CACHE_DAY_TIME       30 * MINUTE
#define GPS_UPDATE_CACHE_HOUR_TIME      30 * MINUTE
#define GPS_UPDATE_CACHE_MINUTE_TIME    10 * SECOND
#define TRAVEL_LOG_TIMER                1  * SECOND

// Devices
Accelerometer           accelerometer;
EnvironmentalSensor     environmental_sensor;
GPS                     gps;
Storage                 storage;
WiFi                    wifi("SSID", "PSK");  // [ ] open wifi-direct configuration server if no wifi is detected after predefined number of times.

// Controllers
ImpactController        impact_controller;
TravelController        travel_controller;

// Data structures
environmental_data      environment;
gps_data                gps_data_;
accelerometer_data      *acceleration = (accelerometer_data*)malloc(sizeof(accelerometer_data));
impact_data             impact;
travel_data             travel;

// Cache update timers.
long environment_cache_timer    = 0;
long gps_year_cache_timer       = 0;
long gps_month_cache_timer      = 0;
long gps_day_cache_timer        = 0;
long gps_hour_cache_timer       = 0;
long gps_minute_cache_timer     = 0;
long travel_recording_timer     = 0;

void setup()
{
        /*
         * It is important that the device is able to setup properly before
         * interrupts may be handled. For this reason, interrupts are disabled
         * before setup begins.
         */
        disable_interrupts();

        // Setup debugging.
        delay(1000);  // UNIX
        Serial.begin(115200);

        // Ensure interrupt is unlatched to prevent accidental logging.
        if (accelerometer.interrupt_is_latched())
                accelerometer.unlatch_interrupt();

        // Assume vehicle is about to begin moving. We don't need wifi yet.
        if (wifi.is_connected())
                disable_wifi();

        // Try to get a satellite connection on startup.
        if (!gps.is_connected_to_satellites())
                gps.connect_to_satellites();

        // [ ] initialize storage

        /*
         * Now that the devices are setup, interrupts may be handled properly
         * within the loop() function. For this reason, interrupts are enabled
         * again.
         */
        enable_interrupts();
}

void loop()
{
        switch (gps.vehicle_state()) {
        case idle:
                // Connect to WiFi.
                if (!wifi.is_connected())
                        enable_wifi();
                // Upload travel and impact logs.
                if (wifi.is_connected()) {
                        upload_impact_log();
                        upload_travel_log();
                }
                break;
        case moving:
                // Update cache.
                update_environment_cache();
                update_gps_cache();
                // We don't need wifi while we're driving.
                if (wifi.is_connected())
                        disable_wifi();
                // Record impact.
                if (accelerometer.interrupt_is_latched()) {
                        log_impact();
                        accelerometer.unlatch_interrupt();
                }
                // Periodicallyt record travel.
                if (time_elapsed(5 * SECOND)) {
                        log_travel();
                }
                break;
        case unknown:
                // We don't need wifi while we're driving.
                if (wifi.is_connected())
                        disable_wifi();
                // Record acceleration.
                if (accelerometer.interrupt_is_latched()) {
                        log_acceleration();
                        accelerometer.unlatch_interrupt();
                }
                // Attempt to get satellite connection.
                if (!gps.is_connected_to_satellites()) {
                        disable_interrupts();
                        gps.connect_to_satellites(GPS_CONNECT_TIMEOUT);
                        enable_interrupts();
                }
                break;
        default:
                Serial.println("Unhandled vehicle state!");
                break;
        }
}

/**
 * Read impact information from sensors when impact is detected.
 *
 * When an impact is detected, it is important that relevant data is collected
 * to ensure the impact may be evaluated by the AI system and road service
 * dispatching personell.
 **/
void accelerometer_z_high_interrupt_ISR /*RAM_ATTR*/()
{
        acceleration = accelerometer.read();
        environment  = environmental_sensor.read();     // [@] accelerate this process by reading from cache
        gps_data_    = gps.read();                      // [@] acceleration this process by reading from cache
}

/**
 * Refresh all cached gps values if update is ready.
 **/
void update_gps_cache()
{
        update_gps_year_cache(GPS_UPDATE_CACHE_YEAR_TIME);
        update_gps_month_cache(GPS_UPDATE_CACHE_MONTH_TIME);
        update_gps_day_cache(GPS_UPDATE_CACHE_DAY_TIME);
        update_gps_hour_cache(GPS_UPDATE_CACHE_HOUR_TIME);
        update_gps_minute_cache(GPS_UPDATE_CACHE_MINUTE_TIME);
}

/**
 * Periodically updates cached year.
 *
 * @param timer update period
 *
 * @see GPS_UPDATE_CACHE_YEAR_TIME
 **/
void update_gps_year_cache(long timer)
{
        if (millis() - gps_year_cache_timer > GPS_UPDATE_CACHE_YEAR_TIME) {
                gps.update_cache(year);
                gps_year_cache_timer = millis();
        }
}

/**
 * Periodically updates cached month.
 *
 * @param timer update period
 *
 * @see GPS_UPDATE_CACHE_MONTH_TIME
 **/
void update_gps_month_cache(long timer)
{
        if (millis() - gps_month_cache_timer > GPS_UPDATE_CACHE_MONTH_TIME) {
                gps.update_cache(month);
                gps_month_cache_timer = millis();
        }
}

/**
 * Periodically updates cached day.
 *
 * @param timer update period
 *
 * @see GPS_UPDATE_CACHE_DAY_TIME
 **/
void update_gps_day_cache(long timer)
{
        if (millis() - gps_day_cache_timer > GPS_UPDATE_CACHE_DAY_TIME) {
                gps.update_cache(day);
                gps_day_cache_timer = millis();
        }
}

/**
 * Periodically updates cached hour.
 *
 * @param timer update period
 *
 * @see GPS_UPDATE_CACHE_HOUR_TIME
 **/
void update_gps_hour_cache(long timer)
{
        if (millis() - gps_hour_cache_timer > GPS_UPDATE_CACHE_HOUR_TIME) {
                gps.update_cache(hour);
                gps_hour_cache_timer = millis();
        }
}

/**
 * Periodically updates cached minute.
 *
 * @param timer update period
 *
 * @see GPS_UPDATE_CACHE_MINUTE_TIME
 **/
void update_gps_minute_cache(long timer)
{
        if (millis() - gps_minute_cache_timer > GPS_UPDATE_CACHE_MINUTE_TIME){
                gps.update_cache(minute);
                gps_minute_cache_timer = millis();
        }
}

/**
 * Periodically updates cached environment information.
 *
 * @param timer update period
 *
 * @see ENV_UPDATE_CACHE_TIME
 **/
void update_environment_cache()
{
        if (millis() - environment_cache_timer > ENV_UPDATE_CACHE_TIME) {
                environmental_sensor.update_cache();
                environment_cache_timer = millis();
        }
}

/**
 * Writes non-gps acceleration data to temporary storage.
 *
 * @note interrupts are disabled during this process to prevent data corruption.
 **/
void log_acceleration()
{
        disable_interrupts();
        // [ ] impact impact_controller.create_non_gps_impact(
                // environment,
                //* update_gps_month_cache(long timer)/ acceleration,
                // ACCELERATION_BUFFER_LENGTH);
        impact_controller.log_impact(storage, impact);
        enable_interrupts();
}

/**
 * Write complete impact information to temporary storage.
 *
 * @note interrupts are disabled during this process to prevent data corruption.
 **/
void log_impact()
{
        disable_interrupts();
        impact = impact_controller.create_impact(gps_data_,
                                                 environment,
                                                 acceleration);
        impact_controller.log_impact(storage, impact);
        enable_interrupts();
}

/**
 * Write travel information to temporary storage.
 *
 * @note interrupts are disabled during this process to prevent data corruption.
 **/
void log_travel()
{
        disable_interrupts();
        travel = travel_controller.create_travel(gps_data_, environment);
        if (travel_controller.buffer_is_full())
                travel_controller.log_travel(storage);
        enable_interrupts();
}

/**
 * Returns true if the input time has elapsed for travel recording.
 *
 * @param time: timer duration
 *
 * @see travel_recording_timer
 **/
bool time_elapsed(long time)
{
        if (millis() - travel_recording_timer > time) {
                travel_recording_timer = millis();
                return true;
        } else {
                return false;
        }
}

/**
 * Attempt to connect to wifi.
 * Wifi connection attempt ends after time set by WIFI_CONNECT_TIMEOUT.
 *
 * @note interrupts are disabled during this process to prevent unexpected
 *       errors.
 *
 * @see WIFI_CONNECT_TIMEOUT
 **/
void enable_wifi()
{
        disable_interrupts();
        wifi.connect(WIFI_CONNECT_TIMEOUT);
        enable_interrupts();
}

/**
 * Disconnect from and turn off wifi.
 *
 * @note interrupts are disabled during this process to prevent unexpected
 *       errors.
 **/
void disable_wifi()
{
        disable_interrupts();
        wifi.disconnect();
        enable_interrupts();
}

/**
 * Uploads a single impact log, oldest first.
 *
 * @note Interrupts are disabled during this process to prevent unexpcted
 *       errors.
 **/
void upload_impact_log()
{
        disable_interrupts();
        impact_controller.upload_impact("http://roadreporter.us/map/upload_impact.php");
        enable_interrupts();
}

/**
 * Uploads a single travel log, oldest first.
 *
 * @note Interrupts are disabled during this process to prevent unexpected
 *       errors.
 **/
void upload_travel_log()
{
        disable_interrupts();
        travel_controller.upload_travel("http://roadreporter.us/map/upload_travel.php");
        enable_interrupts();
}
