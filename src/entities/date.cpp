#include "date.h"

/**
 * Default constructor
 *
 * @returns Date
 **/
Date::Date()
{
        // nothing to do here...
}

/**
 * Default destructor
 **/
Date::~Date()
{
        // nothing to do here...
}

/**
 * Return the character pointer "YYYY-MM-DD"
 *
 * @returns "YYYY-MM-DD"
 **/
char *Date::to_string()
{
        char *result = (char*)malloc(32 * sizeof(char));
        sprintf(result, "%04d-%02d-%02d", *year, *month, *day);
        return result;
}

void Date::set_date(uint16_t year, uint8_t month, uint8_t day)
{
        set_year(year);
        set_month(month);
        set_day(day);
}

/**
 * Points this date's year, month, to input addresses.
 * When the source's date is updated, this object's date will automatically
 * reflect these changes.
 *
 * @param year  pointer
 * @param month pointer
 * @param day   pointer
 **/
void Date::link_date(uint16_t *year, uint8_t *month, uint8_t *day)
{
        if (year != NULL)
                this->year = year;
        if (month != NULL)
                this->month = month;
        if (day != NULL)
                this->day = day;
}

void Date::set_year(uint16_t year)
{
        *this->year = year;
}

void Date::set_month(uint8_t month)
{
        *this->month = month;
}

void Date::set_day(uint8_t day)
{
        *this->day = day;
}

uint16_t Date::get_year()
{
        return *year;
}

uint8_t Date::get_month()
{
        return *month;
}

uint8_t Date::get_day()
{
        return *day;
}
