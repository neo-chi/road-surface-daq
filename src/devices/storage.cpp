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

void Storage::mkdir(char *path)
{
        Serial.print("Made directory at: ");
        Serial.println(path);
}

void Storage::mv(char *path_from, char *path_to)
{
        Serial.print("Moving ");
        Serial.print(path_from);
        Serial.print(" to ");
        Serial.println(path_to);
}

void Storage::read(char *path, char **out)
{
        Serial.print("Reading file at path: ");
        Serial.println(path);
}

void Storage::rm(char *path)
{
        Serial.print("Removing file/directory at path: ");
        Serial.println(path);
}

void Storage::write(char *path, char *message)
{
        Serial.print("Writing to file at path: ");
        Serial.println(path);
        Serial.print("Content: ");
        Serial.println(message);
}

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
