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
