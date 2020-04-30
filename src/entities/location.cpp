/*******************************************************************************
 * @file	location.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

#include "location.h"

Location::Location()
{
        // nothing to do here...
}
Location::~Location()
{
        // nothing to do here...
}

/**
 * Returns the chracter array "{latitude},{longitude}" where latitude
 * and longitude are floats.
 *
 * @returns "{latitude},{longitude}"
 **/
char *Location::to_string()
{
        // convert to google maps format
        float latitude {((float)*_latitude) / 10000000};
        float longitude{((float)*_longitude) / 10000000};
        char  *result  {(char*)malloc(64 * sizeof(char))};
        sprintf(result, "latitude=%0.6f,longitude=%0.6f", latitude, longitude);
        return result;
}

void Location::set_location(int32_t latitude, int32_t longitude)
{
        set_latitude(latitude);
        set_longitude(longitude);
}

void Location::link_location(int32_t *latitude, int32_t *longitude)
{
        this->_latitude = latitude;
        this->_longitude = longitude;
}

int32_t Location::set_latitude(int32_t latitude)
{
        *this->_latitude = latitude;
}

int32_t Location::set_longitude(int32_t longitude)
{
        *this->_longitude = longitude;
}

int32_t Location::get_latitude()
{
        return *this->_latitude;
}

int32_t Location::get_longitude()
{
        return *this->_longitude;
}
