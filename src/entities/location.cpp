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
        float _latitude  = ((float)*latitude) / 10000000;
        float _longitude = ((float)*longitude) / 10000000;
        char *result     = (char*)malloc(64 * sizeof(char));
        sprintf(result, "latitude=%0.6f,longitude=%0.6f", _latitude, _longitude);
        return result;
}

void Location::set_location(int32_t latitude, int32_t longitude)
{
        set_latitude(latitude);
        set_longitude(longitude);
}

void Location::link_location(int32_t *latitude, int32_t *longitude)
{
        this->latitude = latitude;
        this->longitude = longitude;
}

int32_t Location::set_latitude(int32_t latitude)
{
        *this->latitude = latitude;
}

int32_t Location::set_longitude(int32_t longitude)
{
        *this->longitude = longitude;
}

int32_t Location::get_latitude()
{
        return *this->latitude;
}

int32_t Location::get_longitude()
{
        return *this->longitude;
}
