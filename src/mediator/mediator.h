#ifndef _ROAD_SURFACE_DAQ_MEDIATOR_H
#define _ROAD_SURFACE_DAQ_MEDIATOR_H

#include "Arduino.h"
#include "data_collector_event.h"
#include "storage_event.h"
#include "uploader_event.h"

class DataCollector;
class Storage;
class Uploader;
class Mediator {
  public:
    Mediator();
    void Update(data_collector_event event);
    void Update(storage_event event);
    void Update(uploader_event event);
  private:
    DataCollector *data_collector;
    Storage *storage;
    Uploader *uploader;
};

#endif
