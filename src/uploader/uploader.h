#pragma once

#include "Arduino.h"
#include "storage.h"
#include "wifi.h"
#include "travel_parser.h"
#include "impact_parser.h"

#define TRV ".trv"
#define IMP ".imp"

class Uploader
{
        public:
                Uploader();
                ~Uploader();
                void begin(Storage *storage, WiFiManager *wifi);
                void end();
        private:
                Storage      *storage;
                WiFiManager  *wifi;
                ImpactParser *impact_parser = new ImpactParser;
                TravelParser *travel_parser = new TravelParser;
                String __extension_of(File file);
                void   __upload_travel(File file);
                void   __upload_impact(File file);
};
