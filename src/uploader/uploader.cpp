#include "uploader.h"

void Uploader::begin(Storage *storage, WiFiManager *wifi)
{
        File file {storage->get_uploadable_file()};

        if (!wifi->is_connected())
                wifi->connect();

        if (wifi->is_connected() && file != NULL) {
                Serial.printf("uploader: uploading %s...\n", file.name());
                if (_extension_of(file) == TRV) {
                        _upload_travel(file);

                } else if (_extension_of(file) == IMP) {
                        _upload_impact(file);

                } else {
                        Serial.print("invalid file...");
                }
                Serial.println("complete!");
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
