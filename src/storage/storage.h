/******************************************************************************
 * @file	storage.h
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-24
 * @see		https://github.com/reecechimento/road-surface-daq
 *
 * The storage class is responsible for handling the filesystem made possible
 * by the SD card attached to this embedded system. It provides the following
 * file management features:
 *      - making directories
 *      - renaming directories
 *      - removing directories
 *      - writing to files
 *      - reading from files
 *      - moving files
 *      - renaming files
 *      - removing files
*******************************************************************************/
#pragma once

#include "Arduino.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class Storage
{
        public:
                Storage();
                void            begin();
                void            mkdir(char *path);
                void            mv(char *path_from, char *path_to);
                void            rename(char *path_from, char *path_to);
                void            rm(char *path);
                void            rmdir(char *path);
                void            read(char *path); // TODO -> return string?
                //char            **read(char *path); // TODO -> return string?
                void            write(char *path, char *message);
                void            write(char *path, uint8_t *buf, size_t bytes_to_write);
        private:
                fs::FS &file_system;
};