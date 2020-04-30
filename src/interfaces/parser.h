#pragma once

#include "SD.h"
#include "uploadable.h"

class Parser
{
        public:
                Parser() {}
                ~Parser() {}
                virtual Uploadable *parse_file(File file) = 0;
};
