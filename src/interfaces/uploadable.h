#pragma once

#include "HTTPClient.h"

#define UPLOADABLE_MAX_UPLOADS 2000

/**
 * The Uploadable interfaces requires implementing classes to provide a method
 * that uploads its data to a database.
 **/
class Uploadable
{
        public:
                Uploadable() {};
                ~Uploadable() {};
                virtual bool upload() = 0;
                void         add_upload(String upload);
        protected:
                String       _uploads[UPLOADABLE_MAX_UPLOADS];
                int          _num_uploads = 0;

};
