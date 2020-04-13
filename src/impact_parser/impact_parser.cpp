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
