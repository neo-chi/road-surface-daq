#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

/********************************CONFIGURATION*********************************/
/**
 * DEBUG: enable or disable serial monitor messages.
 **/
#define DEBUG 1  // 1 -> Enable serial monitor messages.
#define DEBUG_VERBOSE 0
#define print_impact	Serial.printf("%s", impact_log);
/******************************************************************************/

#include "Adafruit_LIS3DH.h"
static Adafruit_LIS3DH	accelerometer;
static const size_t	acc_buf_len			= 5;
static float		x[acc_buf_len];
static float		y[acc_buf_len];
static float		z[acc_buf_len];
static const size_t	impact_log_len			= 2048;  // 2kB
static char		impact_log[impact_log_len];

static const size_t	capture_buf_len			= 10;
static int		capture_buf[capture_buf_len];

static const size_t 	rolling_buf_len			= capture_buf_len;
static int		rolling_buf[rolling_buf_len];
size_t			rolling_buf_idx 		= 0;
int			rolling_buf_val  		= 0;
int			new_value_idx			= 0;

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
		,	2				// Priority [Highest 3 -> Lowest 0]
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

	for (;;)  // A task *MUST* never return or exit.
	{
		if (rolling_buffer_is_full()) {
			//Serial.println("Buffer is full");
			//Serial.print("!");
			capture_rolling_buffer();
			// read_accelerometer()
			roll_buffer();  // adds new accelerometer values to rollling buffer
		}

		if (!rolling_buffer_is_full()) {
			//Serial.println("Rolling Buffer Not Full");
			fill_rolling_buffer();
			// read_accelerometer()
			//roll_buffer();
		}

		//read_accelerometer();
		//generate_impact_log();
		delay(2000);
	}
}

/**
 * Returns true if rolling buffer has been filled with accelerometer values.
 *
 * @param rolling_buf_idx
 * @param rolling_buf_len
 *
 * @returns bool
 **/
bool rolling_buffer_is_full()
{
	// Serial.printf("rolling_buf_idx: %d\trolling_buf_len: %d\n", rolling_buf_idx, rolling_buf_len);
	return rolling_buf_idx >= rolling_buf_len;
}

/**
 * Sets the capture buffer values to the rolling buffer values ordered from
 * oldest values to newest values.
 *
 * @param rolling_buf		input
 * @param capture_buf		output
 * @param new_value_idx		index of newest value in rolling buffer
 * @param rolling_buf_len	size of rolling buffer
 **/
void capture_rolling_buffer()
{

	int len = 0;
	// Populate capture buffer with oldest rolling buffer values first.
	for (int i = new_value_idx; i < rolling_buf_len; i++) {
		capture_buf[len] = rolling_buf[i];
		len++;

		#if DEBUG_VERBOSE
		Serial.println();
		Serial.println("Working from newest value of rolling buffer");
		Serial.printf("old value index: %d\trolling buf val: %d\n", i, rolling_buf[i]);
		Serial.printf("new value index: %d\n", new_value_idx);
		#endif
	}
	// Then populate the rest of the capture buffer with new rolling buffer values.
	for (int i = 0; i < new_value_idx; i++) {
		capture_buf[len] = rolling_buf[i];
		len++;

		#if DEBUG_VERBOSE
		Serial.println();
		Serial.println("Working from start of rolling buffer");
		Serial.printf("old value index: %d\trolling buf val: %d\n", i, rolling_buf[i]);
		Serial.printf("new value index: %d\n", new_value_idx);
		#endif
	}

	#if DEBUG
	size_t bytes_written = 0;
	size_t offset = 0;
	for (int i = 0; i < capture_buf_len; i++) {
		bytes_written = sprintf(impact_log + offset, "%03d ", capture_buf[i]);
		offset       += bytes_written;
	}
	Serial.printf("Capture: [ %s]\n", impact_log);
	#endif
}

/**
 *
 **/
void roll_buffer()
{
	// Add a new value to the rolling buffer
	rolling_buf[new_value_idx] = rolling_buf_val;

	// Specify where the newest values begin.
	new_value_idx++;
	rolling_buf_val++;

	// Don't go out of bounds...
	if (new_value_idx == rolling_buf_len)
		new_value_idx = 0;
}

/**
 * Adds values to the rolling buffer until it is full and ready for capture.
 *
 * @param rolling_buf
 * @param rolling_buf_idx
 * @param rolling_buf_val	value assigned to rolling buffer
 **/
void fill_rolling_buffer()
{
	while (!rolling_buffer_is_full()) {
		rolling_buf[rolling_buf_idx] = rolling_buf_val;
		rolling_buf_idx++;
		rolling_buf_val++;
	}
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
					"x: %0.3f\ty: %0.3f\tz: %0.3f\n",
						x[i],
						y[i],
						z[i]);
		len_offset += bytes_written;
	}

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
		delay(10000);
	}
}
