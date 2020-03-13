#pragma once

#include "Arduino.h"

/* Interface  */ class Uploadable
{
        public:
                ~Uploadable() {};
                /*
                 * Returns the location header String pointing to the upload PHP
                 * script for this data.
                 */
                virtual String location() = 0;
                /*
                 * Returns the POST url-encoded-form String for this data.
                 */
                virtual String post() = 0;
        private:
                Uploadable& operator = (const Uploadable&);
};
