#pragma once

#include "Arduino.h"

/*
 * location - stores gps latitude and longitude in google maps format.
 * @latitude
 * @longitude
 */
struct location
{
        const float latitude;
        const float longitude;
};
