/*******************************************************************************
 * @file	datetime.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

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
        char *result{(char*)malloc(32 * sizeof(char))};
        sprintf(result, "datetime=%s %s", Date::to_string(), Time::to_string());
        return result;
}
