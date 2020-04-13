#include "travel_parser.h"

TravelParser::TravelParser() : Parser()
{
        // nothing to do here...
}

Uploadable *TravelParser::parse_file(File file)
{
        Serial.printf("travel_parser: parsing %s...\n", file.name());
        static HTTPClientUploadable *uploadable = new HTTPClientUploadable();
        while (file.available()) {
                String POST {file.readStringUntil('\n')};
                POST.replace(" ", "+");      // datetime=YYYY-MM-DD+HH:MM:SS
                POST.replace(":", "\\%3A");  // datetime=YYYY-MM-DD+HH\%3AMM\%3ASS
                POST.replace(",", "&");      // used when posting multiple items
                uploadable->add_upload(POST);
        }
        Serial.println("complete!");
        return uploadable;
}
