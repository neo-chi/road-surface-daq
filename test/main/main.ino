/*******************************************************************************
 * @file	main.ino
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-21
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/

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
#define THIRTY_MINUTES          1800000
#define TEN_MINUTES             600000
#define TEN_SECONDS             10000
#define ONE_SECOND              1000

// Update these to control functions.
#define ACCELERATION_BUF_LEN            512
#define GPS_CONNECT_TIMEOUT             TEN_SECONDS
#define WIFI_CONNECT_TIMEOUT            TEN_SECONDS
#define ENV_UPDATE_CACHE_TIME           TEN_MINUTES
#define GPS_UPDATE_CACHE_YEAR_TIME      THIRTY_MINUTES
#define GPS_UPDATE_CACHE_MONTH_TIME     THIRTY_MINUTES
#define GPS_UPDATE_CACHE_DAY_TIME       THIRTY_MINUTES
#define GPS_UPDATE_CACHE_HOUR_TIME      THIRTY_MINUTES
#define GPS_UPDATE_CACHE_MINUTE_TIME    TEN_SECONDS
#define TRAVEL_LOG_TIMER                ONE_SECOND
#define VEHICLE_STATE_UPDATE_TIME       ONE_SECOND
// [ ] Make update time depend on gps time

// Devices
Accelerometer           *accelerometer        = new Accelerometer;
EnvironmentalSensor     *environmental_sensor = new EnvironmentalSensor;
GPS                     *gps                  = new GPS;
Storage                 *storage              = new Storage;
WiFiManager             *wifi                 = new WiFiManager("SSID", "PSK");

// Controllers
ImpactController        impact_controller;
TravelController        travel_controller;

/**
 * Read impact information from sensors when impact is detected.
 *
 * When an impact is detected, it is important that relevant data is collected
 * to ensure the impact may be evaluated by the AI system and road service
 * dispatching personell.
 **/
void IRAM_ATTR accelerometer_z_high_ISR()
{
        accelerometer->interrupt_has_occured = true;
        //Serial.println("INTERRUPT");
}

// User-defined configurations
#define ACCELEROMETER_INT_PIN           16
#define GPS_VEHICLE_IS_MOVING_SPEED     200  // UNITS: mm/s
#define ACCELEROMETER_DATARATE          LIS3DH_DATARATE_LOWPOWER_1K6HZ
#define ACCELEROMETER_RANGE             LIS3DH_RANGE_8_G
#define IMPACT_LOG_SIZE_MAX             32000  // 32000 B
#define TRAVEL_RECORD_PERIOD            5000   // 5 seconds

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

        // Setup accelerometer interrupt
        pinMode(ACCELEROMETER_INT_PIN, INPUT_PULLDOWN);
        attachInterrupt(ACCELEROMETER_INT_PIN, accelerometer_z_high_ISR, RISING);

        accelerometer->begin();
        gps->begin();
        storage->begin();
        environmental_sensor->begin();
        wifi->begin();

        impact_controller.attach(accelerometer);
        impact_controller.attach(gps);
        impact_controller.attach(environmental_sensor);
        impact_controller.attach(storage);
        impact_controller.attach(wifi);

        travel_controller.attach(gps);
        travel_controller.attach(environmental_sensor);
        travel_controller.attach(storage);
        travel_controller.attach(wifi);

        // Ensure interrupt is unlatched to prevent accidental logging.
        accelerometer->unlatch_interrupt();
        gps->connect_to_satellites(GPS_CONNECT_TIMEOUT);

        // Assume vehicle is about to begin moving. We don't need wifi yet.
        disable_wifi();

        // Try to get a satellite connection on startup.
        //if (!gps->is_connected_to_satellites())
               //gps->connect_to_satellites();

        /*
         * Now that the devices are setup, interrupts may be handled properly
         * within the loop() function. For this reason, interrupts are enabled
         * again.
         */
        enable_interrupts();
}

void loop()
{
        // TODO: remove log files after uploading
        //switch (get_vehicle_state()) {
        switch(MOVING) {
        case IDLE:
                disable_interrupts();  // we don't want to record impacts that oddly occur while idle...
                if (wifi->is_connected())
                        upload_logs();
                else
                        enable_wifi();
                break;
        case MOVING:
                enable_interrupts();
                if (impact_detected())
                        log_impact();
                if (time_elapsed(TRAVEL_RECORD_PERIOD))
                        log_travel();
                accelerometer->read(PRE_IMPACT);
                update_environment_cache();
                update_gps_cache();
                break;
        case UNKNOWN:
                enable_interrupts();
                if (impact_detected())
                        log_acceleration(); // there's a problem here!
                if (!gps->is_connected_to_satellites())
                        gps->connect_to_satellites(GPS_CONNECT_TIMEOUT);
                accelerometer->read(PRE_IMPACT);
                break;
        default:
                disable_interrupts();  // we don't want to record impacts that oddly occur while idle...
                Serial.println("ERROR: unhandled vehicle state!");
                break;
        }
}

/**
 * Encapsulates log uploading.
 **/
void upload_logs()
{
        upload_impact_log();
        upload_travel_log();
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
        impact_controller.upload_impact(""); // TODO: put link here
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
        travel_controller.upload_travel(""); // TODO: put link here
        enable_interrupts();
}

/**
 * Write complete impact information to temporary storage.
 *
 * @note interrupts are disabled during this process to prevent data corruption.
 **/
void log_impact()
{
        long start_time = millis();
        disable_interrupts();
        accelerometer->read(POST_IMPACT);
        gps->read();
        impact_controller.create_impact();
        impact_controller.log_impact();
        accelerometer->unlatch_interrupt();
        enable_interrupts();
        long elapsed_time = millis() - start_time;

        Serial.printf("Impact logging took %u seconds!\n", elapsed_time);

}

/**
 * Write travel information to temporary storage.
 *
 * @note interrupts are disabled during this process to prevent data corruption.
 **/
void log_travel()
{
        if (travel_controller.buffer_is_full()) {
                disable_interrupts();
                travel_controller.log_travel();
                enable_interrupts();
        } else {
                travel_controller.create_travel();
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
        accelerometer->read(POST_IMPACT);
        impact_controller.log_acceleration();
        accelerometer->unlatch_interrupt();
        enable_interrupts();
}

/**
 * Refresh all cached gps values if update is ready.
 **/
void update_gps_cache()
{
        update_gps_year_cache();
        update_gps_month_cache();
        update_gps_day_cache();
        update_gps_hour_cache();
        update_gps_minute_cache();
}

/**
 * Periodically updates cached year.
 *
 * @param timer update period
 *
 * @see GPS_UPDATE_CACHE_YEAR_TIME
 **/
void update_gps_year_cache()
{
        static long gps_year_cache_timer = 0;
        if (millis() - gps_year_cache_timer > GPS_UPDATE_CACHE_YEAR_TIME) {
                gps->update_cache(YEAR);
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
void update_gps_month_cache()
{
        static long gps_month_cache_timer = 0;
        if (millis() - gps_month_cache_timer > GPS_UPDATE_CACHE_MONTH_TIME) {
                gps->update_cache(MONTH);
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
void update_gps_day_cache()
{
        static long gps_day_cache_timer = 0;
        if (millis() - gps_day_cache_timer > GPS_UPDATE_CACHE_DAY_TIME) {
                gps->update_cache(DAY);
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
void update_gps_hour_cache()
{
        static long gps_hour_cache_timer = 0;
        if (millis() - gps_hour_cache_timer > GPS_UPDATE_CACHE_HOUR_TIME) {
                gps->update_cache(HOUR);
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
void update_gps_minute_cache()
{
        static long gps_minute_cache_timer = 0;
        if (millis() - gps_minute_cache_timer > GPS_UPDATE_CACHE_MINUTE_TIME){
                gps->update_cache(MINUTE);
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
        static long environment_cache_timer = 0;
        if (millis() - environment_cache_timer > ENV_UPDATE_CACHE_TIME) {
                environmental_sensor->update_cache();
                environment_cache_timer = millis();
        }
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
        static long travel_recording_timer = 0;
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
        wifi->connect(WIFI_CONNECT_TIMEOUT);
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
        wifi->disconnect();
        enable_interrupts();
}

/**
 * Periodically get the vehicle state.
 *
 * @note edit VEHICLE_STATE_UPDATE_TIME to change how often the vehicle state
 *              is checked.
 **/
vehicle_state get_vehicle_state()
{
        static long elapsed_time = 0;
        static vehicle_state current_vehicle_state = gps->get_vehicle_state();
        if (millis() - elapsed_time >= VEHICLE_STATE_UPDATE_TIME) {
                current_vehicle_state = gps->get_vehicle_state();
                elapsed_time = millis();
        }
        return current_vehicle_state;
}

/**
 * Clarifies the use of accelerometer->interrupt_is_latched for this
 * implementation.
 **/
bool impact_detected()
{
        return accelerometer->interrupt_is_latched();
}
