#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/********************************CONFIGURATION*********************************/
/**
 * DEBUG: enable or disable serial monitor messages.
 **/
#define DEBUG 0  // 0 -> Enable serial monitor messages.
#define print_impact	Serial.printf("%s", impact_log);
/******************************************************************************/


#include "Adafruit_LIS3DH.h"
static Adafruit_LIS3DH		accelerometer;
static const size_t		acc_buf_len			= 5;
static float			x[acc_buf_len];
static float			y[acc_buf_len];
static float			z[acc_buf_len];
static const size_t		impact_log_len			= 2048;  // 2kB
static char			impact_log[impact_log_len];

// define two tasks for println1 and println2
void TaskPrintLn_1(void *pvParameters);
void TaskPrintLn_2(void *pvParameters);

// setup function runs once when you press reset or power the board.
void setup()
{
	delay(1000);
        Serial.begin(115200);

        // Now set up two tasks to run indepenedently.
	xTaskCreatePinnedToCore(
		TaskPrintLn_1
		,	"TaskPrintLn_1"			// A name for people to understand
		,	2048				// Stack size
		,	NULL
		,	2				// Priority [Highest 3 -> Lowest 0]
		,	NULL
		,	ARDUINO_RUNNING_CORE);

	xTaskCreatePinnedToCore(
		TaskPrintLn_2				// Task function pointer
		,	"TaskPrintLn_2"			// Task name for people
		,	2048				// Stack size
		,	NULL				// Paramaters
		,	1				// Priority
		,	NULL				// TaskHandle_t created Task
		, 	ARDUINO_RUNNING_CORE);

	// Now the task scheduler is automatically started.
}

void loop()
{
	// Empty. Things done in Tasks.
}

void TaskPrintLn_1(void *pvParameters)
{
	(void) pvParameters;

	// Task initialization...
	accelerometer.setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
	accelerometer.setRange(LIS3DH_RANGE_16_G);
	accelerometer.begin(LIS3DH_DEFAULT_ADDRESS);
	accelerometer.printSensorDetails();

	for (;;)  // A task *MUST* never return or exit.
	{
		read_accelerometer();
		size_t len_offset 	 = 0;
		size_t bytes_written 	 = 0;
		for (size_t i = 0; i < acc_buf_len; i++) {
			bytes_written = sprintf(impact_log + len_offset,
						"x: %0.3f\ty: %0.3f\tz: %0.3f\n",
						 x[i],
						 y[i],
						 z[i]);
			len_offset += bytes_written;
		}
		delay(2000);

		// Display log_impact buffer and file size.
		#if DEBUG
		bytes_written = len_offset;
		Serial.printf("-------------------------------------------\n");
		//Serial.printf("%s", impact_log);
		print_impact;  // using preprocessor macro
		Serial.printf("Impact Log File Size: %u\n", len_offset);
		Serial.printf("-------------------------------------------\n");
		#endif
	}
}

/**
 * Store accelerometer batch-read to individual axis buffers.
 *
 * @see const size_t acc_buf_len
 * @see float x[acc_buf_len]
 * @see float y[acc_buf_len]
 * @see float z[acc_buf_len]
 *
 * @returns x  global x[acc_buf_len]
 * @returns y  global y[acc_buf_len]
 * @returns z  global z[acc_buf_len]
 **/
void read_accelerometer()
{
	for (size_t i = 0; i < acc_buf_len; i++) {
		accelerometer.read();
		x[i] = accelerometer.x_g;
		y[i] = accelerometer.y_g;
		z[i] = accelerometer.z_g;
	}
}

void TaskPrintLn_2(void *pvParameters)
{
	(void) pvParameters;

	// Task initialization goes here...

	for (;;)
	{
		Serial.println();
		Serial.println("Task 2 doing nothing.");
		Serial.println();
		delay(10000);
	}
}

