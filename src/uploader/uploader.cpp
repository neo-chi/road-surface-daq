/*******************************************************************************
 * @file	uploader.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

#include "uploader.h"

/**
 * Establish a WiFi connection and begin uploading files from storage.
 *
 * @param wifi - WiFi driver object
 * @param storage - data storage object
 **/
void Uploader::begin(Storage *storage, WiFiManager *wifi)
{
        File file {storage->get_uploadable_file()};

        if (!file)
                return;

        if (file.size() == 0) {
                storage->archive(file);
                return;
        }

        if (wifi->is_connected()) {
                delay(5000);  // give WiFi time to recover...
                Serial.printf("uploader: uploading %s...\n", file.name());

                if (   _extension_of(file) == ".trv"
                    || _extension_of(file) == ".TRv") {
                        if (travel_parser->parse_file(file)->upload())
                                storage->archive(file);

                } else if (   _extension_of(file) == ".imp"
                           || _extension_of(file) == ".IMp") {
                        if (impact_parser->parse_file(file)->upload())
                                storage->archive(file);

                } else {
                        Serial.print("invalid file...");
                }
                Serial.println("complete!");

        } else {
                delay(5000);
                wifi->connect();
        }
}

void Uploader::_upload_travel(File file)
{
        const bool upload_successful{travel_parser->parse_file(file)->upload()};
        if (upload_successful)
                storage->archive(file);
}

void Uploader::_upload_impact(File file)
{
        const bool upload_successful{impact_parser->parse_file(file)->upload()};
        file.close();
        if (upload_successful)
                storage->archive(file);
}

String Uploader::_extension_of(File file)
{
        const String filename  {file.name()};
        const String extension {filename.substring(filename.lastIndexOf("."))};
        return extension;
}

void Uploader::end()
{
        wifi->disconnect();
}

Uploader::Uploader()
{
        // nothing to do here...
}

Uploader::~Uploader()
{
        // nothing to do here...
}
