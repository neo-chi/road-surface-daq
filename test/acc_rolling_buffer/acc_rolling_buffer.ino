#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "Arduino.h"

int global_variable = 0;

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
		,	1024				// Stack size
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

	for (;;)  // A task *MUST* never return or exit.
	{
		Serial.printf("Task 1 global_variable++\n");
		global_variable++;
		Serial.printf("Task 1 set global var: %d\n", global_variable);
		Serial.printf("Task 1 Waiting...\n");
		Serial.printf("\n");
		vTaskDelay(10000);  // 12 seconds
	}
}

void TaskPrintLn_2(void *pvParameters)
{
	(void) pvParameters;

	// Task initialization goes here...

	for (;;)
	{
		Serial.printf("Task 2 global_variable++\n");
		global_variable++;
		Serial.printf("Task 2 set global var: %d\n", global_variable);
		Serial.printf("Task 2 Waiting...\n");
		Serial.printf("\n");
		vTaskDelay(5000);  // 1.5 seconds
	}
}
