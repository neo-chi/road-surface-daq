/*******************************************************************************
 * @file	date.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

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
        char *result{(char*)malloc(32 * sizeof(char))};
        sprintf(result, "%04d-%02d-%02d", *_year, *_month, *_day);
        return result;
}

void Date::set_date(uint16_t year, uint8_t month, uint8_t day)
{
        set_year(year);
        set_month(month);
        set_day(day);
}

void Date::set_year(uint16_t year)
{
        *this->_year = year;
}

void Date::set_month(uint8_t month)
{
        *this->_month = month;
}

void Date::set_day(uint8_t day)
{
        *this->_day = day;
}

uint16_t Date::get_year()
{
        return *_year;
}

uint8_t Date::get_month()
{
        return *_month;
}

uint8_t Date::get_day()
{
        return *_day;
}
