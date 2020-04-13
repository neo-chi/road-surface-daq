/******************************************************************************
 * @file	storage.cpp
 * @author	reece chimento
 * @version	1.0
 * @since	2019-03-24
 * @see		https://github.com/reecechimento/road-surface-daq
/******************************************************************************/
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
        if (SD.begin()) {
                Serial.println("Succesfully mounted SD card!");
                Serial.println("Created storage.");
        } else {
                Serial.println("SD card mount failed!");
                Serial.println("Storage will not work properly!");
        }
}

/**
 * @interface Loggable
 **/
void Storage::write(Loggable *loggable)
{
        Serial.printf("storage: logging %s...", loggable->get_path());
        mkdir(loggable->get_dir());
        write(loggable->get_path(), loggable->get_log(), loggable->get_size());
        loggable->reset();
        Serial.println("complete!");
}

File Storage::get_uploadable_file(const char *dir)
{
        File ROOT = file_system.open(dir);
        File next_file;
        File directory;
        while (next_file = ROOT.openNextFile()) {
                if (!next_file.isDirectory() && _is_uploadable(next_file)) {
                        return next_file;
                }
                if (next_file.isDirectory()) {
                        directory = next_file;
                        while (next_file = directory.openNextFile()) {
                                if (_is_uploadable(next_file)) {
                                        return next_file;
                                }
                        }
                }
        }
}

void Storage::get_uploadable_file(File *file, int level)
{
        File next_file;
        File directory;
        while (next_file = file->openNextFile()) {
                Serial.println(next_file.name());
                if (_is_uploadable(next_file)) {
                        *file = next_file;
                        return;
                }
                if (next_file.isDirectory()) {
                        directory = next_file;
                        while (next_file = directory.openNextFile()) {
                                Serial.println(next_file.name());
                                if (_is_uploadable(next_file)) {
                                        *file = next_file;
                                        return;
                                }
                        }
                }
        }
}

bool Storage::dir_has_uploadable_file(const char *dir)
{
        Serial.printf("searching directory %s\n", dir);
        File directory {file_system.open(dir)};
        while (File file = directory.openNextFile()) {
                if (_is_uploadable(file))
                        return true;
        }

}

bool Storage::_is_uploadable(File file)
{
        // Serial.printf("storage: checking if %s is uploadable...", file.name());
        const String filename  {file.name()};
        const String extension {filename.substring(filename.lastIndexOf("."))};
        if (extension == ".trv" || extension == ".TRv" || extension == ".tRv") {
                // Serial.printf("complete! %s is uploadable\n", file.name());
                // Serial.println("complete!");
                return true;
        } else if (extension == ".imp") {
                // Serial.printf("complete! %s is uploadable\n", file.name());
                // Serial.println("complete!");
                return true;
        } else {
                // Serial.printf("complete! %s is NOT uploadable\n", file.name());
                // Serial.println("complete!");
                return false;
        }
}

/**
 * Appends the file extension ".up" to the file.
 *
 * @note files with this extension will be ignored when uploading.
 **/
void Storage::archive(File file)
{
        Serial.printf("storage: archiving %s...", file.name());
        char *old_filename = (char*)malloc(64 * sizeof(char));
        strcpy(old_filename, file.name());

        char *new_filename = (char*)malloc(64 * sizeof(char));
        strcpy(new_filename, old_filename);
        strcat(new_filename, ".up");

        file_system.rename(
                file.name(),
                new_filename
        );
        // Serial.printf("complete! %s -> %s\n", old_filename, new_filename);
        Serial.println("complete!");

}


String Storage::ls(const char *dir) // TODO: pass a function to call on each file
{
        File _dir{file_system.open(dir)};
        Serial.printf("DIR:  %s\n", _dir.name());
        while (File file {_dir.openNextFile()}) {
                if (file.isDirectory()) {
                        ls(file.name());
                } else {
                        if (_is_uploadable(file));
                                return file.name();
                }
        }
}

/**
 * Make a directory.
 *
 * @note include full path name in UNIX style (/dir/dir/...).
 **/
void Storage::mkdir(char *path)
{
        Serial.printf("storage: making directory at \"%s\"...\n", path);
        if (file_system.exists(path)) {
                Serial.printf("The directory \"%s\" already exists!\n", path);
        } else {
                Serial.printf("The directory \"%s\" does not exist, creating...", path);
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
void Storage::mv(char *path_from, char *path_to)
{
        Serial.printf("storage: moving \"%s\" to \"%s\"...", path_from, path_to);
>>>>>>> src(*): add IRAM_ATTR to methods, increase speed:src/storage/storage.cpp
        if (file_system.rename(path_from, path_to))
                Serial.println("Complete!");
        else
                Serial.println("Failure!");
}

/**
 * Read a file's contents.
 *
 * @note include full path in UNIX style.
 **/
char **Storage::read(char *path)
{
        Serial.printf("Reading file at %s...", path);

        bool file_exists = false;
        bool file_opened = false;

        if (file_system.exists(path)) {
                Serial.printf("%s found...", path);
                file_exists = true;
        } else {
                Serial.printf("%s not found...Failure!", path);
                file_exists = false;
        }

        File file = file_system.open(path, FILE_READ);
        if (file) {
                Serial.printf("reading \"%s\"\n", path);
                file_opened = true;
        } else {
                Serial.printf("unexpected error...Failure!");
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
        if (file_system.exists(path_from) && !(file_system.exists(path_to))) {
                if (file_system.rename(path_from, path_to))
                        Serial.printf("complete!\n");
                else
                        Serial.printf("failure!\n");
        } else {
                Serial.printf("%s not found...Failure!", path_from);
        }
}

/**
 * Remove a file.
 *
 * @note include full path in UNIX style.
 **/
void Storage::rm(char *path)
{
        Serial.printf("storage: removing file at \"%s\"...", path);
        if (file_system.exists(path)) {
                Serial.printf("file found, removing...");
                if (file_system.remove(path))
                        Serial.printf("Complete!\n");
                else
                        Serial.printf("Failure!\n");
        } else {
                Serial.printf("file not found! quitting.\n");
        }
}

/**
 * Remove a directory and its contents.
 *
 * @note include full path in UNIX style.
 **/
void Storage::rmdir(char *path)
{
        Serial.printf("storage: removing directory at \"%s\"...", path);
        if (file_system.exists(path)) {
                Serial.printf("directory found, removing...");
                if (file_system.rmdir(path))
                        Serial.printf("Complete!\n");
                else
                        Serial.printf("Failure!\n");
        } else {
                Serial.printf("directory not found! quitting.\n");
        }
}

/**
 * Write or append a message to a file.
 *
 * @note include full path in UNIX style.
 **/
void Storage::write(char *path, char *message)
{
        if (file_system.exists(path)) {
                //Serial.printf("%s exists, appending \"%s\"...", path, message);
                File file = file_system.open(path, FILE_APPEND);
                if (file) { // if file opened...
                        file.printf("%s", message);
                        Serial.println("Complete!");
                } else {
                        Serial.println("Failure!");
                }
                file.close();
        } else {
                //Serial.printf("%s created, writing \"%s\"...", path, message);
                File file = file_system.open(path, FILE_WRITE);
                if (file) { // if file opened...
                        file.printf("%s", message);
                        Serial.println("Complete!");
                } else {
                        Serial.println("Failure!");
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
void Storage::write(char *path, uint8_t *buf, size_t bytes_to_write)
{
        // Log whether file is being overwritten.
        if (file_system.exists(path))
                Serial.printf("\"%s\" exists, overwriting...\n", path);
        else
                Serial.printf("\"%s\" does not exist, writing new file...\n", path);

        // Open file for writing/overwriting.
        File file = file_system.open(path, FILE_WRITE);
        if (file) {
                Serial.printf("\"%s\" opened! Writing...\n", path);
        } else {
                Serial.printf("could not open \"%s\"...exiting!\n", path);
                return;
        }

        // Write buffer to file.
        size_t buf_idx          = 0;  // buffer pointer offset.
        size_t bytes_written    = 0;
        size_t bytes_rem        = bytes_to_write;
        while (bytes_rem) {
                //Serial.printf("bytes remaining = %u\n", bytes_rem);
                if (bytes_rem > 512) {
                        bytes_written   = file.write(buf + buf_idx, 512);
                        bytes_rem       -= bytes_written;
                        buf_idx         += bytes_written;
                        //Serial.printf("wrote %u bytes\n", bytes_written);
                } else {
                        bytes_written   = file.write(buf + buf_idx, bytes_rem);
                        bytes_rem       -= bytes_written;
                        buf_idx         += bytes_written;
                        //Serial.printf("wrote %u bytes\n", bytes_written);
                }
        }
        Serial.printf("file write to \"%s\" complete!\n", path);
        file.close();
}

void IRAM_ATTR Storage::write(char *path, char *buf, size_t bytes_to_write)
{
       write(path, (uint8_t*)buf, bytes_to_write);
}
