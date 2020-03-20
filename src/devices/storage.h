#pragma once

#include "Arduino.h"
//#include "FS.h"
//#include "SD.h"
//#include "SPI.h"

class Storage
{
        public:
                Storage();
                void mkdir(char *path);
                void mv(char *path_from, char *path_to);
                void rm(char *path);
                void read(char *path, char **out);
                void write(char *path, char *message);
                void write(char *path, char **buffer, int buffer_size);
        private:
 //               fs::FS file_system;
};