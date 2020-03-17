#pragma once

#include "Arduino.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class Storage
{
        public:
                void mkdir(String path);
                void mv(String from, String to);
                void rm(String path);
                void read(String path, String *out);
                void write(String path, String message);
                void write(String path, String *buffer, int buffer_size);
        private:
                fs::FS file_system;
};