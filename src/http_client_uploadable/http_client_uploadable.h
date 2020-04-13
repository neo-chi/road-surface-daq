#pragma once

#include "Arduino.h"
#include "uploadable.h"
#include "HTTPClient.h"

class HTTPClientUploadable : public Uploadable
{
        public:
                HTTPClientUploadable(char *URL);
                ~HTTPClientUploadable();
                bool upload();
        private:
                char *_URL{(char*)malloc(255 * sizeof(char))};
};
