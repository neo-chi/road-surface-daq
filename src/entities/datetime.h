#pragma once

#include "Arduino.h"
#include "date.h"
#include "_time.h"

class DateTime : public Date, public Time
{
        public:
                DateTime();
                ~DateTime();
                char *to_string();
                void  set_datetime(Date date, Time time);
                void  link_datetime(Date *date, Time *time);
                Date  get_date();
                Time  get_time();
        protected:
                Date *_date = new Date;
                Time *_time = new Time;
};
