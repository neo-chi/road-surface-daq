#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/********************************CONFIGURATION*********************************/
/**
 * DEBUG: enable or disable serial monitor messages.
 **/
#define DEBUG 0  // 1 -> Enable serial monitor messages.
#define DEBUG_VERBOSE 0
#define print_impact	Serial.printf("%s", impact_log);
/******************************************************************************/

#include "Adafruit_LIS3DH.h"
#include "storage.h"
static Adafruit_LIS3DH	accelerometer;
static const size_t	acc_buf_len			= 32;
static float		x[acc_buf_len]{1, 2, 3, 4, 5};
static float		y[acc_buf_len]{11, 12, 13, 14, 15};
static float		z[acc_buf_len]{101, 102, 103, 104, 105};
static const size_t	impact_log_len			= 1024;  // 2kB
char		impact_log[impact_log_len];
size_t impact_log_size = impact_log_len;


// define two tasks for println1 and println2
void accelerometer_rolling_buffer(void *pvParameters);
void main_control(void *pvParameters);

// setup function runs once when you press reset or power the board.
void setup()
{
	delay(1000);
        Serial.begin(115200);

        // Now set up two tasks to run indepenedently.
	xTaskCreatePinnedToCore(
		accelerometer_rolling_buffer
		,	"accelerometer_rolling_buffer"			// A name for people to understand
		,	2048				// Stack size
		,	NULL
		,	3				// Priority [Highest 3 -> Lowest 0]
		,	NULL
		,	ARDUINO_RUNNING_CORE);

	xTaskCreatePinnedToCore(
		main_control				// Task function pointer
		,	"main_control"			// Task name for people
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

void accelerometer_rolling_buffer(void *pvParameters)
{
	(void) pvParameters;

	// Task initialization...
	accelerometer.setDataRate(LIS3DH_DATARATE_LOWPOWER_1K6HZ);
	accelerometer.setRange(LIS3DH_RANGE_16_G);
	accelerometer.begin(LIS3DH_DEFAULT_ADDRESS);
	accelerometer.printSensorDetails();
	Storage storage;

	for (;;)  // A task *MUST* never return or exit.
	{
		Serial.println("About to begin...");
		delay(10000);
		Serial.println("5");
		delay(1000);
		Serial.println("4");
		delay(1000);
		Serial.println("3");
		delay(1000);
		Serial.println("2");
		delay(1000);
		Serial.println("1");
		delay(1000);
		Serial.println("GO!!!");
		delay(500);

		//for (int i = 0; i < acc_buf_len; i++) {
			//printf("[ x: %0.3f\ty: %0.3f\tz: %0.3f ]\n", x[i], y[i], z[i]);
		//}
		//printf("\n");

		//roll_buffer_left();
		read_accelerometer();
		Serial.println("Complete!");
		delay(3000);

		generate_impact_log();

		Serial.println("Creating path...");
		//static int i = 0;
		//char       *path;
		//sprintf(path, "/imp%03d.log", i);
		//Serial.printf("path: %s", path);

		storage.write("/impact.log", (uint8_t*)impact_log, impact_log_size);

		delay(30000);
	}
}

void roll_buffer_left()
{
	accelerometer.read();
	for (size_t i = 0; i < acc_buf_len - 1; i++) {
		x[i] = x[i + 1];
		y[i] = y[i + 1];
		z[i] = z[i + 1];
	}
	x[acc_buf_len - 1] = accelerometer.x_g;
	y[acc_buf_len - 1] = accelerometer.y_g;
	z[acc_buf_len - 1] = accelerometer.z_g;
}

/**
 * Format individual accelerometer axis buffers to a file log string.
 *
 * @see float x[acc_buf_len]    input
 * @see float y[acc_buf_len]    input
 * @see float z[acc_buf_len]    input
 * @see char  impact_log[2048]	output
 *
 * @param x[]  x acceleration buffer
 * @param y[]  y acceleration buffer
 * @param z[]  z acceleration buffer
 *
 * @returns impact_log
 **/
void generate_impact_log()
{
	size_t len_offset 	 = 0;  // Offset the impact_log pointer so we don't overwrite.
	size_t bytes_written 	 = 0;
	for (size_t i = 0; i < acc_buf_len; i++) {
		bytes_written = sprintf(impact_log + len_offset,
					"%0.3f\t%0.3f\t%0.3f\n",
						x[i],
						y[i],
						z[i]);
		len_offset += bytes_written;
	}
	impact_log_size = len_offset;

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

/**
 * Save accelerometer batch-read to individual axis buffers.
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

void main_control(void *pvParameters)
{
	(void) pvParameters;

	// Task initialization goes here...

	for (;;)
	{
		//Serial.println();
		//Serial.println("Task 2 doing nothing.");
		//Serial.println();
		delay(10000000);
	}
}

