/*******************************************************************************
 * @file	http_client_uploadable.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-04-09
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * Implements Uploadable interface, allowing for uploading to database using
 * an HTTP request.
*******************************************************************************/

#pragma once

#include "Arduino.h"
#include "uploadable.h"
#include "HTTPClient.h"

class HTTPClientUploadable : public Uploadable
{
        public:
                HTTPClientUploadable();
                ~HTTPClientUploadable();
                bool upload();
};
