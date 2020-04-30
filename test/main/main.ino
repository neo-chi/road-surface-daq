/*******************************************************************************
 * @file	main.ino
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-21
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

#include "impact.h"
#include "acceleration.h"
#include "travel.h"

#include "accelerometer.h"
#include "gps.h"
#include "environmental_sensor.h"

#include "uploader.h"

static Accelerometer       *accelerometer        = new Accelerometer;
static GPS                 *gps                  = new GPS;
static EnvironmentalSensor *environmental_sensor = new EnvironmentalSensor;
static Storage             *storage              = new Storage;
static WiFiManager         *wifi                 = new WiFiManager("Network",
                                                                  "configur");

// Acceleration        *acceleration         = new Acceleration;
static Impact              *impact               = new Impact;
static Travel              *travel               = new Travel;

static Uploader            *uploader             = new Uploader;

// Clarity functions
#define disable_interrupts() cli()
#define enable_interrupts()  sei()

#define VEHICLE_STATE_UPDATE_TIME 500
#define GPS_CONNECT_TIMEOUT       30000

// User-defined configurations
#define ACCELEROMETER_INT_PIN 17

/**
 * Allow reading impact information from sensors when impact is detected.
 *
 * When an impact is detected, it is important that relevant data is collected
 * to ensure the impact may be evaluated by the AI system and road service
 * dispatching personell.
 **/
void IRAM_ATTR accelerometer_z_high_ISR()
{
        accelerometer->interrupt_has_occured = true;
        Serial.println("INTERRUPT");
}

/**
 * Enables accelerometer interrupt detection, starts sensors, and initializes
 * data pointers.
 **/
void setup()
{
        /*
         * It is important that the device is able to setup properly before
         * interrupts may be handled. For this reason, interrupts are disabled
         * before setup begins.
         */
        disable_interrupts();

        // Setup debugging.
        delay(1000);  // Required for UNIX machines...
        Serial.begin(115200);

        initialize_sensors();
        setup_accelerometer_interrupt_on_pin(17);

        // Try to get a GPS connection before starting...
        gps->connect_to_satellites(GPS_CONNECT_TIMEOUT);

        /*
         * Now that the devices are setup, interrupts may be handled properly
         * within the loop() function. For this reason, interrupts are enabled
         * again.
         */
        enable_interrupts();
}

/**
 * Change behaviour based on the movement state of the vehicle.
 *
 * The vehicle as three known vehicle states, each with their respective
 * behaviours:
 * 1. MOVING  the device records impact information when an impact is detected.
 * 2. IDLE    the device attempts to upload recorded data to the database.
 * 3. UNKOWN  the continuously attempts to restablish GPS satelltite connection.
 *
 * A fourth, default state, handles all other unexpected vehicles states.
 * In this case "default" the device will attempt to restablsih GPS satelltite
 * connection in order to determine vehicle state.
 **/
void loop()
{
        switch(get_vehicle_state()) {
        case IDLE:
                disable_interrupts();
                uploader->begin(storage, wifi); // dependency injection
                break;
        case MOVING:
                enable_interrupts();
                if (impact_detected())
                        log_impact();
                if (time_elapsed(TRAVEL_LOG_PERIOD))
                        log_travel();
                gps->read();
                accelerometer->read();
                break;
        case UNKNOWN:
                disable_interrupts();
                if (!gps->is_connected_to_satellites())
                        gps->connect_to_satellites(GPS_CONNECT_TIMEOUT);
                break;
        default:
                disable_interrupts();
                if (!gps->is_connected_to_satellites())
                        gps->connect_to_satellites(GPS_CONNECT_TIMEOUT);
                Serial.println("ERROR: unhandled vehicle state!");
                break;
        }
}

/**
 * Write complete impact information to temporary storage.
 *
 * @note interrupts are disabled during this process to prevent data corruption.
 **/
void log_impact()
{
        disable_interrupts();
        accelerometer->read(POST_IMPACT);
        impact->log();  // generate formatted impact log string.
        storage->write(impact);  // save the loggable data.
        accelerometer->unlatch_interrupt();
        enable_interrupts();
}

/**
 * Write travel information to temporary storage.
 *
 * @note interrupts are disabled during this process to prevent data corruption.
 **/
void log_travel()
{
        if (!travel->log_is_full()) {
                travel->log();
        } else {
                disable_interrupts();
                storage->write(travel);
                enable_interrupts();
        }
}

/**
 * Returns true if the input time has elapsed for travel recording.
 *
 * @param time - timer duration
 *
 * @see TRAVEL_LOG_PERIOD
 *
 * @returns bool - true if input duration has elapsed
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
 * Periodically get the vehicle state.
 *
 * @note edit VEHICLE_STATE_UPDATE_TIME to change how often the vehicle state
 *              is checked.
 *
 * @returns vehicle_state - {IDLE, MOVING, UNKNOWN}.
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
 * Clarifies the use of accelerometer->interrupt_is_latched() for this
 * implementation.
 *
 * @see Accelerometer::interrupt_is_latched()
 *
 * @returns bool - true if acclerometer interrupt event was detected.
 **/
bool impact_detected()
{
        return accelerometer->interrupt_is_latched();
}

/**
 * Enables accelerometer interrupt event detection on the specified pin.
 *
 * @note the interrupt service routine is predefined.
 *
 * @see accelerometer_z_high_ISR()
 *
 * @param pin interrupt event detection pin
 **/
void setup_accelerometer_interrupt_on_pin(const int pin)
{
        pinMode(pin, INPUT_PULLDOWN);
        attachInterrupt(pin, accelerometer_z_high_ISR, RISING);
}

/**
 * Starts all sensors and point data objects to the corresponding sensor data
 * objects.
 *
 * @note data object members implememt pointers that must be set to sensor
 *       data addresses.
 *       By using pointers, with care, data access rate and data operation
 *       speed is increased by elimnated the need to copy data from one block
 *       of memory to another.
 *       Because the device must collect and log data quickly, pointers to
 *       data are used rather than memory-independent data members.
 **/
void initialize_sensors()
{
        // Start and configure all sensors.
        accelerometer->begin();
        gps->begin();
        environmental_sensor->begin();

        // Start storage (SD card).
        storage->begin();

        // unlatch accelerometer interrupt to prevent accidiental readings.
        accelerometer->unlatch_interrupt();

        // Set travel data member pointers.
        travel->point_to(gps->location);
        travel->point_to(gps->datetime);
        travel->point_to(gps->datetime);
        travel->point_to(gps->vehicle_speed);

        // Set impact data members.
        impact->point_to(gps->vehicle_speed);
        impact->point_to(gps->datetime);
        impact->point_to(gps->location);
        impact->point_to(accelerometer->acceleration);
}
