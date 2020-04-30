/*******************************************************************************
 * @file	http_client_uploadable.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-09
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

#include "http_client_uploadable.h"

HTTPClientUploadable::HTTPClientUploadable() : Uploadable()
{
        // nothing to do here...
}

HTTPClientUploadable::~HTTPClientUploadable()
{
        // nothing to do here...
}


/**
 * Uploads all data stored in this uploadable object via HTTP POST.
 *
 * @returns bool - true if file upload is successful
 **/
bool HTTPClientUploadable::upload()
{
        bool __return_val = false;
        static const char _URL[]{"http://roadreporter.us/data/log_upload.php"};
        HTTPClient http;
        _num_uploads--;
        while (_num_uploads >= 0) {
                Serial.printf(
                        "uploadable: uploading %s via HTTP to %s...",
                        _uploads[_num_uploads].c_str(),
                        _URL
                );

                // Perform upload
                http.begin(_URL);
                http.setReuse(true);
                http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                const int    http_code {http.POST(_uploads[_num_uploads])};
                const String payload   {http.getString()};
                _num_uploads--;

                if (http_code == 200) {
                        __return_val = true;
                        Serial.printf(
                                "complete! http_code: %d -> %s\n",
                                http_code,
                                payload.c_str()
                        );

                } else {
                        __return_val = false;
                        http.end();
                        _num_uploads = 0;
                        Serial.printf(
                                "error uploading... http_code: %d -> %s exiting\n",
                                http_code,
                                payload.c_str()
                        );
                        break;
                }
        } // end while
        http.end();
        _num_uploads = 0;
        return __return_val;
}
