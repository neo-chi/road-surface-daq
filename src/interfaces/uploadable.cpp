/*******************************************************************************
 * @file	uploadable.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-10
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/

#include "uploadable.h"

void Uploadable::add_upload(String upload)
{
        // Serial.print("uploadable: adding ");
        // Serial.print(upload);
        // Serial.print(" to upload queue...");
        if (_num_uploads < UPLOADABLE_MAX_UPLOADS) {
                _uploads[_num_uploads] = upload;
                _num_uploads++;
        }
        // Serial.println("complete!");
}
