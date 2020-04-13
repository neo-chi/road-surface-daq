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
#include "loggable.h"
#include "parser.h"
#include "http_client_uploadable.h"

class Storage
{
        public:
                Storage();
                void            begin();
                void            write(Loggable *loggable);
                File            get_uploadable_file(const char *dir = "/");
                void            get_uploadable_file(File *file, int level);
                bool            dir_has_uploadable_file(const char *dir);
                String          ls(const char *dir = "/");
                void            archive(File file);
        private:
                bool            _is_uploadable(File file);
                void            rename(char *path_from, char *path_to);
                void            mkdir(char *path);
                void            mv(char *path_from, char *path_to);
                void            rm(char *path);
                void            rmdir(char *path);
                void            read(char *path); // TODO -> return string?
                //char            **read(char *path); // TODO -> return string?
                void            write(char *path, char *message);
                void            write(char *path, uint8_t *buf, size_t bytes_to_write);
                void            write(char *path, char *buf, size_t bytes_to_write);
                fs::FS &file_system;
};
