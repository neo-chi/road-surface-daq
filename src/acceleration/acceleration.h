#pragma once

#include "Arduino.h"
#include "loggable.h"
#include "uploadable.h"

#define DEBUG         true
#define DEBUG_VERBOSE 0

#define ACC_PRE_IMPACT_LEN  400
#define ACC_POST_IMPACT_LEN 800
#define ACC_BUF_LEN ACC_PRE_IMPACT_LEN + ACC_POST_IMPACT_LEN

class Acceleration
{
        public:
                Acceleration();
                char *dir();
                char *path();
                char *log();
                size_t size();
                float x[ACC_BUF_LEN];
                float y[ACC_BUF_LEN];
                float z[ACC_BUF_LEN];
};
