#pragma once

#include "Arduino.h"

/* Interface  */ class Loggable
{
        public:
                ~Loggable() {};

                /*
                 * Returns the log String to save this data to a file.
                 */
                virtual String log() = 0;
        private:
                Loggable& operator = (const Loggable&);
};

