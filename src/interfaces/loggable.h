#pragma once

#include "Arduino.h"
#include "date.h"
#include "_time.h"

#define LOGGABLE_LOG_SIZE_MAX      10240
#define LOGGABLE_DIR_SIZE_MAX      64
#define LOGGABLE_FILENAME_SIZE_MAX 64
#define LOGGABLE_PATH_SIZE_MAX     192

/**
 * The Loggable interfaces requires implementing classes to provide a method
 * that writes its data to a file.
 **/
class Loggable
{
        public:
                Loggable() {};
                ~Loggable() {};
                virtual void log()         = 0;
                virtual bool log_is_full() = 0;
                virtual void reset();
                char        *get_dir();
                char        *get_path();
                char        *get_log();
                size_t       get_size();
        protected:
                void   _set_dir(Date date);
                void   _set_filename(Time time, const char *extension);
                void   _set_path(char *_dir, char *_filename);
                char   *_log     {(char*)malloc(LOGGABLE_LOG_SIZE_MAX      * sizeof(char))};
                char   *_dir     {(char*)malloc(LOGGABLE_DIR_SIZE_MAX      * sizeof(char))};
                char   *_path    {(char*)malloc(LOGGABLE_PATH_SIZE_MAX     * sizeof(char))};
                char   *_filename{(char*)malloc(LOGGABLE_FILENAME_SIZE_MAX * sizeof(char))};
                size_t _log_size {0};
};
