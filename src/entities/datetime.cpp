#include "datetime.h"

/**
 * Default constructor
 *
 * @return datetime
 **/
DateTime::DateTime() : Date(), Time()
{

}

/**
 * Default destructor
 **/
DateTime::~DateTime()
{

}

char *DateTime::to_string()
{
        char *result = (char*)malloc(32 * sizeof(char));
        sprintf(result, "datetime=%s %s", Date::to_string(), Time::to_string());
        return result;
}


void DateTime::set_datetime(Date date, Time time)
{
        _date->set_date(date.get_year(), date.get_month(), date.get_day());
        _time->set_time(time.get_hour(), time.get_minute(), time.get_second());
        // set_date(date.get_year(), date.get_month(), date.get_day());
        // set_time(time.get_hour(), time.get_minute(), time.get_second());
}

void  DateTime::link_datetime(Date *date, Time *time)
{
        this->_date = date; // TODO: make sure this works
        this->_time = time;
}

Date DateTime::get_date()
{
        return *this;
}

Time DateTime::get_time()
{
        return *this;
}

// void DateTime::set_date(Date date)
// {
//         *this->date = date;
// }

// void DateTime::set_time(Time time)
// {
//         *this->time = time;
// }
