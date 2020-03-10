#ifndef _ROAD_SURFACE_DAQ_STORAGE_H
#define _ROAD_SURFACE_DAQ_STORAGE_H

#include "Arduino.h"
// @require FS.h
// @require SD.h
// @require SPI.h

class Storage {  // @interface Implements Observable
  public:
    Storage();  // initialize SD, fs = SD
    void read(const String& path, String *buffer, uint16_t buffer_len);  // buffer is output
    void write(const String& path, String *buffer, uint16_t buffer_len);  // buffer is input
    void write(const String& path, String& data);
    bool mkdir(const String& path);
    bool rename(const String& path_from, const String& path_to);
    bool remove(const String& path);
  private:
    // FS::fs &fs
      // fs.mkdir
      // fs.rename --> rename a file or move a file
      // fs.remove
      // fs.open
      // fs.read
      // fs.write
      // fs.close
    // SD.begin(ROOT_DIR = "/")
};

#endif
