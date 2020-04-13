#include "uploadable.h"

void Uploadable::add_upload(String upload)
{
        Serial.print("uploadable: adding ");
        Serial.print(upload);
        Serial.print(" to upload queue...");
        if (_num_uploads < UPLOADABLE_MAX_UPLOADS) {
                _uploads[_num_uploads] = upload;
                _num_uploads++;
                Serial.println("complete!");
        } else {
                Serial.println("failure! maximum uploads reached");
        }
}
