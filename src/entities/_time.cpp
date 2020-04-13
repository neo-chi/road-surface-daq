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
        char *result{(char*)malloc(32 * sizeof(char))};
        sprintf(result, "%02d:%02d:%02d", *_hour, *_minute, *_second);
        return result;
}

void Time::set_time(uint8_t hour, uint8_t minute, uint8_t second)
{
        set_hour(hour);
        set_minute(minute);
        set_second(second);
}

void Time::set_hour(uint8_t hour)
{
        *this->_hour = hour;
}

void Time::set_minute(uint8_t minute)
{
        *this->_minute = minute;
}

void Time::set_second(uint8_t second)
{
        *this->_second = second;
}

uint8_t Time::get_hour()
{
        return *_hour;
}

uint8_t Time::get_minute()
{
        return *_minute;
}

uint8_t Time::get_second()
{
        return *_second;
}
