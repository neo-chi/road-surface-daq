#pragma once

#include "parser.h"
#include "http_client_uploadable.h"

class TravelParser : public Parser
{
        public:
                TravelParser();
                Uploadable *parse_file(File file);
};
