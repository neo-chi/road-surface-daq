#include "rtest.h"

// The String test class is used to identify whether two strings are identical.
StringTest::StringTest(String _name, String _expected, String _experimental)
  : name(_name), expected(_expected), experimental(_experimental) {
  // Nothing to do here.
}

void StringTest::Execute() {
  TestName();
  TestExpected();
  TestExperimental();
  TestExecute();
}

void StringTest::TestName() {
  String message = "TEST: \t\t\t";
  message.concat(name);
  Serial.println(message);
}

void StringTest::TestExpected() {
  String message = "EXPECTED \t\t";
  message.concat(expected);
  Serial.println(message);
}

void StringTest::TestExperimental() {
  String message = "EXPECTED \t\t";
  message.concat(experimental);
  Serial.println(message);
}

void StringTest::TestExecute() {
  if (expected.equals(experimental)) {
    test_pass = true;
    Serial.println("PASS");
    Serial.println();
  } else {
    test_pass = false;
    Serial.println("FAIL");
    Serial.println();
  }

}