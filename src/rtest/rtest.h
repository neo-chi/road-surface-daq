#ifndef _ROAD_SURFACE_DAQ_RTEST_H
#define _ROAD_SURFACE_DAQ_RTEST_H

#include "Arduino.h"

class StringTest {
  public:
    StringTest(String _name, String _expected, String _experimental);
    boolean test_pass = false;
    void Execute();
  private:
    String name = "";
    String expected = "";
    String experimental = "";
    void TestName();
    void TestExpected();
    void TestExperimental();
    void TestExecute();
};

#endif
