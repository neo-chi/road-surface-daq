#include "storage.h"
#include "mediator.h"

Storage::Storage() {
  // SD.begin()
  // this->fs = SD;
}

void Storage::read(const String& path, String* buffer, uint16_t buffer_len) {
  // TODO read from file, store in buffer, return buffer.
}

void Storage::write(const String& path, String& data) {
  // TODO
  String message("Writing ");
  message.concat(data);
  message.concat(" to path: ");
  message.concat(path);
  Serial.println(message);
}

void Storage::write(const String& path, String* buffer, uint16_t buffer_len) {
  // TODO
  String message("Writing\n");
  // Generate a string containing the buffer...?
  for (int buffer_idx = 0; buffer_idx <= buffer_len; buffer_idx++){
    if (!(buffer[buffer_idx].isEmpty())) {
      message.concat(buffer[buffer_idx]);
      message.concat("\n");
    }
  }
  message.concat("to path: ");
  message.concat(path);
  Serial.println(message);
}

bool Storage::mkdir(const String& path) {
  // TODO
  // NOTE check if directory exists.
  // if it does not exist, return true (success)
  Serial.print("Making the directory: ");
  Serial.println(path);
  // else, return false (failure)
}

bool Storage::rename(const String& path_from, const String& path_to) {
  // TODO
  // NOTE check if directory exists.
  // if it does not exist, return true (success)
  String message = "Renaming ";
  message.concat(path_from);
  message.concat(" to ");
  message.concat(path_to);
  Serial.println(message);
  // else, return false (failure)
}

bool Storage::remove(const String& path) {
  // NOTE check if directory exists.
  // if it does not exist, return true (success)
  String message = "Removing ";
  message.concat(path);
  Serial.println(message);
  // else, return false (failure)
}
