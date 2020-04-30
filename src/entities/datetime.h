/*******************************************************************************
 * @file	datetime.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * Extends Date and Time classes. This allows the DateTime class to be passed
 * as both a date and a time.
 * DateTime can be printed in the format:
 *      "YYYY-MM-DD HH:MM:SS"
*******************************************************************************/

#pragma once

#include "Arduino.h"
#include "date.h"
#include "_time.h"

#define SECOND_MILLIS 1000
#define MINUTE_MILLIS 60000
#define HOUR_MILLIS   3600000
#define DAY_MILLIS    86400000

class DateTime : public Date, public Time
{
        public:
                DateTime();
                ~DateTime();
                char *to_string();
};
