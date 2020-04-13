#pragma once

#include "Arduino.h"
#include "date.h"
#include "_time.h"

#define SECOND_MILLIS               1000
#define MINUTE_MILLIS               60000
#define HOUR_MILLIS                 3600000
#define DAY_MILLIS                  86400000

class DateTime : public Date, public Time
{
        public:
                DateTime();
                ~DateTime();
                char *to_string();
};
