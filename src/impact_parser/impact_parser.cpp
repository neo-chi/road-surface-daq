/*******************************************************************************
 * @file	impact_parser.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

#include "impact_parser.h"

/**
 * Default Constructor
 *
 * @returns ImpactParser
 **/
ImpactParser::ImpactParser() : Parser()
{
        // nothing to do here...
}

/**
 * Deletes this ImpactParser
 **/
ImpactParser::~ImpactParser()
{
        // nothing to do here...
}

/**
 * Parse file for impact data.
 *
 * @param file - file to parse
 *
 * @returns uploadable interface
 **/
Uploadable *ImpactParser::parse_file(File file)
{
        Serial.printf("impact_parser: parsing %s...", file.name());
        HTTPClientUploadable *uploadable = new HTTPClientUploadable();
        if (file.available()) { // only reading one line...
                String POST {file.readStringUntil('\n')};
                POST.replace(" ", "+");      // datetime=YYYY-MM-DD+HH:MM:SS
                POST.replace(":", "\\%3A");  // datetime=YYYY-MM-DD+HH\%3AMM\%3ASS
                POST.replace(",", "&");      // used when posting multiple items
                uploadable->add_upload(POST);
        }
        Serial.println("complete!");
        return uploadable;
}
