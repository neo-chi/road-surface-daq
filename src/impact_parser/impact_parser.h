/*******************************************************************************
 * @file	impact_parser.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-09
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * Parses a CSV file for impact data and returns an uploadable interface.
*******************************************************************************/

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
