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

class AccelerationParser : public Parser
{
        public:
                Uploadable *parse_file(File file);
};
