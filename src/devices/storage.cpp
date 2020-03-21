#include "storage.h"

/**
 * Storage Constructor
 *
 * @returns storage object
 */
Storage::Storage()
{
        Serial.println("Created storage.");
}

/**
 * Make a directory.
 *
 * @note include full path name in UNIX style (/dir/dir/...).
 **/
void Storage::mkdir(char *path)
{
        Serial.print("Made directory at: ");
        Serial.println(path);
}

/**
 * Move a file, or rename a file.
 *
 * @note include full path in UNIX style.
 **/
void Storage::mv(char *path_from, char *path_to)
{
        Serial.print("Moving ");
        Serial.print(path_from);
        Serial.print(" to ");
        Serial.println(path_to);
}

/**
 * Read a file's contents.
 *
 * @note include full path in UNIX style.
 **/
char **Storage::read(char *path)
{
        Serial.print("Reading file at path: ");
        Serial.println(path);
}

/**
 * Remove a file.
 *
 * @note include full path in UNIX style.
 **/
void Storage::rm(char *path)
{
        Serial.print("Removing file/directory at path: ");
        Serial.println(path);
}

/**
 * Write or append a message to a file.
 *
 * @note include full path in UNIX style.
 **/
void Storage::write(char *path, char *message)
{
        Serial.print("Writing to file at path: ");
        Serial.println(path);
        Serial.print("Content: ");
        Serial.println(message);
}

/**
 * Write or append a buffer to a file.
 *
 * @note include full path in UNIX style.
 **/
void Storage::write(char *path, char **buffer, int buffer_size)
{
        Serial.print("Writing to file at path: ");
        Serial.println(path);
        Serial.println("Content: ");
        for (int i = 0; i < buffer_size; i++) {
                Serial.printf("%s\n", *buffer);
                ++buffer;  // increment buffer pointer, get next String...
        }
}
