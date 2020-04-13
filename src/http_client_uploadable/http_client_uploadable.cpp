#include "http_client_uploadable.h"

HTTPClientUploadable::HTTPClientUploadable(char *URL) : Uploadable()
{
        _URL  = URL;
}

HTTPClientUploadable::~HTTPClientUploadable()
{
        // nothing to do here...
}

bool HTTPClientUploadable::upload()
{
        bool __return_val = false;
        HTTPClient http;
        while (_num_uploads > 0) {
                Serial.printf(
                        "uploadable: uploading %s via HTTPS client to %s...",
                        _uploads[_num_uploads].c_str(),
                        _URL
                );

                // Perform upload
                http.begin(_URL);
                http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                const int    http_code {http.POST(_uploads[_num_uploads])};
                const String payload   {http.getString()};
                http.end();
                _uploads[_num_uploads].clear(); // remove the uploaded item
                _num_uploads--;

                if (http_code == 200) {
                        __return_val = true;
                        Serial.printf(
                                "complete! http_code: %d -> %s\n",
                                http_code,
                                payload.c_str()
                        );
                        continue;
                } else {
                        __return_val = false;
                        _num_uploads = 0;
                        Serial.printf(
                                "error uploading... http_code: %d -> %s exiting\n",
                                http_code,
                                payload.c_str()
                        );
                        break;
                }
        } // end while
}
