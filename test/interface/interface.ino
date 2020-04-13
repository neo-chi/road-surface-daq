#include "impact.h"
#include "acceleration.h"
#include "travel.h"

#include "accelerometer.h"
#include "gps.h"
#include "environmental_sensor.h"

#include "uploader.h"

Accelerometer       *accelerometer        = new Accelerometer;
GPS                 *gps                  = new GPS;
EnvironmentalSensor *environmental_sensor = new EnvironmentalSensor;
Storage             *storage              = new Storage;
WiFiManager         *wifi                 = new WiFiManager("FBI van 2", "2059030897");

// Acceleration        *acceleration         = new Acceleration;
Impact              *impact               = new Impact;
Travel              *travel               = new Travel;

Uploader            *uploader             = new Uploader;

// Clarity functions
#define disable_interrupts() cli()
#define enable_interrupts()  sei()

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
#define ACCELEROMETER_INT_PIN 17

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

        storage->begin();
        accelerometer->begin();
        gps->begin();
        accelerometer->unlatch_interrupt();
        // environmental_sensor->begin();

        // Ensure interrupt is unlatched to prevent accidental logging.
        // gps->connect_to_satellites(GPS_CONNECT_TIMEOUT);

        travel->point_to(gps->location);
        travel->point_to(gps->datetime);
        travel->point_to(gps->datetime);
        travel->point_to(gps->vehicle_speed);

        impact->point_to(gps->vehicle_speed);
        impact->point_to(gps->datetime);
        impact->point_to(gps->location);
        impact->point_to(accelerometer->acceleration);

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
                // if (wifi->is_connected())
                //         upload_logs();
                // else
                //         enable_wifi();
                uploader->begin(storage, wifi); // dependency injection
                break;
        case MOVING:
                enable_interrupts();
                if (impact_detected())
                        log_impact();
                if (time_elapsed(TRAVEL_LOG_PERIOD))
                        log_travel();
                accelerometer->read();
                gps->populate();
                // update_environment_cache();
                // update_gps_cache();
                break;
        case UNKNOWN:
                enable_interrupts();
                if (impact_detected())
                        log_acceleration(); // there's a problem here!
                if (!gps->is_connected_to_satellites())
                        gps->connect_to_satellites(GPS_CONNECT_TIMEOUT);
                accelerometer->read();
                break;
        default:
                disable_interrupts();  // we don't want to record impacts that oddly occur while idle...
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
        long start_time = millis();

        disable_interrupts();
        accelerometer->read(POST_IMPACT);
        impact->log();
        storage->write(impact);
        accelerometer->unlatch_interrupt();
        enable_interrupts();

        long elapsed_time = millis() - start_time;
        Serial.printf("impact logging took %u ms!\n", elapsed_time);
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
                long start_time = millis();
                disable_interrupts();
                storage->write(travel);
                enable_interrupts();
                long elapsed_time = millis() - start_time;
                Serial.printf("travel logging took %u ms!\n", elapsed_time);
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
        //TODO: impact_controller.log_acceleration();
        accelerometer->unlatch_interrupt();
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
