#include "_time.h"

/**
 * Default constructor
 *
 * @returns Time
 **/
Time::Time()
{
        // nothing to do here...
}

/**
 * Default destructor
 **/
Time::~Time()
{
        // nothing to do here...
}

/**
 * Return the character pointer "HH:MM:SS"
 *
 * @returns "HH:MM:SS"
 **/
char *Time::to_string()
{
        char *result = (char*)malloc(32 * sizeof(char));
        sprintf(result, "%02d:%02d:%02d", *hour, *minute, *second);
        return result;
}

void Time::set_time(uint8_t hour, uint8_t minute, uint8_t second)
{
        set_hour(hour);
        set_minute(minute);
        set_second(second);
}

/**
 * Points this time's hour, minute, and second to input addresses.
 * When the source's time is updated, this object's time will automatically
 * reflect these changes.
 *
 * @param hour   pointer
 * @param minute pointer
 * @param second pointer
 **/
void Time::link_time(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
        if (hour != NULL)
                this->hour = hour;
        if (minute != NULL)
                this->minute = minute;
        if (second != NULL)
                this->second = second;
}

void Time::set_hour(uint8_t hour)
{
        *this->hour = hour;
}

void Time::set_minute(uint8_t minute)
{
        *this->minute = minute;
}

void Time::set_second(uint8_t second)
{
        *this->second = second;
}

uint8_t Time::get_hour()
{
        return *hour;
}

uint8_t Time::get_minute()
{
        return *minute;
}

uint8_t Time::get_second()
{
        return *second;
}
