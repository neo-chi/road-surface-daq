#include "uploader.h"

Uploader::Uploader() {
  Serial.println("Created an Uploader");
}

void Uploader::Upload(const String& location_header, const String& post_data) {
  String message = "Uploading:  ";
  message.concat(post_data);
  message.concat(" to ");
  message.concat(location_header);
  Serial.println(message);
}
