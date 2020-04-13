#pragma once

#include "Arduino.h"
#include "parser.h"
#include "http_client_uploadable.h"

class ImpactParser : public Parser
{
        public:
                ImpactParser();
                ~ImpactParser();
                Uploadable *parse_file(File file);
};
