/******************************************************************************
 * @file	storage.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-24
 * @see		https://github.com/reecechimento/road-surface-daq
*******************************************************************************/
#include "storage.h"
#define SIZE_READ_BUFFER 2048
#define SIZE_CHAR_ARRAY  16

/**
 * Storage Constructor
 *
 * @returns storage object
 */
Storage::Storage() : file_system(SD)
{

}

void Storage::begin()
{
        if (SD.begin())
                Serial.println("storage: succesfully mounted SD card!");
        else
                Serial.println("storage: SD card mount failed!");
}

/**
 * Make a directory.
 *
 * @note include full path name in UNIX style (/dir/dir/...).
 **/
void IRAM_ATTR Storage::mkdir(char *path)
{
        Serial.print("storage: making directory at ");
        Serial.print(path);
        Serial.print("...\n");
        if (file_system.exists(path)) {
                Serial.printf("The directory %s already exists!", path);
        } else {
                Serial.printf("The directory %s does not exist, creating...", path);
                if (file_system.mkdir(path))
                        Serial.println("complete!");
                else
                        Serial.println("failure! Unexpected error");
        }
}

/**
 * Move a file, or rename a file.
 *
 * @note include full path in UNIX style.
 **/
void IRAM_ATTR Storage::mv(char *path_from, char *path_to)
{
        Serial.print("storage: moving ");
        Serial.print(path_from);
        Serial.print(" to ");
        Serial.print(path_to);
        Serial.print("... ");
        if (file_system.rename(path_from, path_to))
                Serial.println("complete!");
        else
                Serial.println("failure!");
}

/**
 * Read a file's contents.
 *
 * @note include full path in UNIX style.
 **/
void IRAM_ATTR Storage::read(char *path)
{
        Serial.printf("storage: reading file at %s...", path);

        bool file_exists = false;
        bool file_opened = false;

        if (file_system.exists(path)) {
                Serial.printf("%s found...", path);
                file_exists = true;
        } else {
                Serial.printf("%s not found...failure!", path);
                file_exists = false;
        }

        File file = file_system.open(path, FILE_READ);
        if (file) {
                Serial.printf("reading \"%s\"\n", path);
                file_opened = true;
        } else {
                Serial.printf("unexpected error...failure!\n");
                file_opened = false;
        }

        if (file_exists && file_opened) {
                while (file.available()) {
                        char *content = (char *)malloc(512 * sizeof(char));
                        size_t len = 512;
                        size_t bytes_read = file.readBytes(content, len);
                        for (int i = 0; i < bytes_read; i++) {
                                Serial.write(*content);
                                ++content;
                        }
                }
        }
}

/**
 * Renames a file.
 **/
void Storage::rename(char *path_from, char *path_to)
{
        Serial.printf("storage: renaming \"%s\" to \"%s\"...", path_from, path_to);
        if (file_system.exists(path_from)) {
                Serial.printf("found \"%s\"...", path_from);
                if (!file_system.exists(path_to)) {
                        Serial.printf("\"%s\" available...", path_to);
                        if (file_system.rename(path_from, path_to))
                                Serial.printf("complete!\n");
                        else
                                Serial.printf("failure!\n");
                } else {
                        Serial.printf("\"%s\" not available...failure!\n",
                                      path_to);
                }
        } else {
                Serial.printf("%s not found...failure!", path_from);
        }
}

/**
 * Remove a file.
 *
 * @note include full path in UNIX style.
 **/
void IRAM_ATTR Storage::rm(char *path)
{
        Serial.printf("storage: removing file at %s ...", path);
        if (file_system.exists(path)) {
                Serial.printf("file found, removing...");
                if (file_system.remove(path))
                        Serial.printf("complete!\n");
                else
                        Serial.printf("failure!\n");
        } else {
                Serial.printf("file not found! quitting.");
        }
}

/**
 * Remove a directory and its contents.
 *
 * @note include full path in UNIX style.
 **/
void Storage::rmdir(char *path)
{
        Serial.printf("storage: removing directory at %s ...", path);
        if (file_system.exists(path)) {
                Serial.printf("directory found, removing...");
                if (file_system.rmdir(path))
                        Serial.printf("complete!\n");
                else
                        Serial.printf("failure!\n");
        } else {
                Serial.printf("directory not found! quitting.");
        }
}

/**
 * Write or append a message to a file.
 *
 * @note include full path in UNIX style.
 **/
void IRAM_ATTR Storage::write(char *path, char *message)
{
        if (file_system.exists(path)) {
                //Serial.printf("%s exists, appending \"%s\"...", path, message);
                File file = file_system.open(path, FILE_APPEND);
                if (file) { // if file opened...
                        file.printf("%s", message);
                        Serial.println("complete!");
                } else {
                        Serial.println("failure!");
                }
                file.close();
        } else {
                //Serial.printf("%s created, writing \"%s\"...", path, message);
                File file = file_system.open(path, FILE_WRITE);
                if (file) { // if file opened...
                        file.printf("%s", message);
                        Serial.println("complete!");
                } else {
                        Serial.println("failure!");
                }
                file.close();
        }
}

/**
 * Write or append a buffer to a file.
 *
 * @param path:           full path to file in UNIX style
 * @param buf:            input data
 * @param bytes_to_write: length of filled data in buf
 *
 * @note include full path in UNIX style.
 * @note if file exists, it will be OVERWRITTEN.
 **/
void IRAM_ATTR Storage::write(char *path, uint8_t *buf, size_t bytes_to_write)
{
        // Log whether file is being overwritten.
        if (file_system.exists(path))
                Serial.printf("%s exists, overwriting...\n", path);
        else
                Serial.printf("%s does not exist, writing new file...\n", path);

        // Open file for writing/overwriting.
        File file = file_system.open(path, FILE_WRITE);
        if (file) {
                Serial.printf("%s opened! Writing...\n", path);
        } else {
                Serial.printf("could not open %s...exiting!\n", path);
                return;
        }

        // Write buffer to file.
        size_t buf_idx          = 0;  // buffer pointer offset.
        size_t bytes_written    = 0;
        size_t bytes_rem        = bytes_to_write;
        while (bytes_rem) {
                Serial.printf("bytes remaining = %u\n", bytes_rem);
                if (bytes_rem > 512) {
                        bytes_written   = file.write(buf + buf_idx, 512);
                        bytes_rem       -= bytes_written;
                        buf_idx         += bytes_written;
                        Serial.printf("wrote %u bytes\n", bytes_written);
                } else {
                        bytes_written   = file.write(buf + buf_idx, bytes_rem);
                        bytes_rem       -= bytes_written;
                        buf_idx         += bytes_written;
                        Serial.printf("wrote %u bytes\n", bytes_written);
                }
        }
        Serial.printf("file write to %s complete!\n", path);
        file.close();
}
