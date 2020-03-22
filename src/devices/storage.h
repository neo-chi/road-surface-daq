#pragma once

#include "Arduino.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class Storage
{
        public:
                Storage();
                void mkdir(char *path);
                void mv(char *path_from, char *path_to);
                void rename(char *path_from, char *path_to);
                void rm(char *path);
                void rmdir(char *path);
                char **read(char *path);
                void write(char *path, char *message);
                void write(char *path, uint8_t *buf, size_t bytes_to_write);
        private:
                fs::FS &file_system;
};