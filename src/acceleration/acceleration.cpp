#include "acceleration.h"

// The Acceleration class stores accelerometer x, y, and z axis data.
//
// If data for a given axis is not recorded, the value is replaced with a
// constant NOT_RECORDED defined as -100. When printing a string, the
// values not recorded will be displayed as NULL.
Acceleration::Acceleration(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

String Acceleration::toString() {
  String return_string = "";

  if (_axis_not_recorded(x)) {
    return_string.concat("NULL");
    return_string.concat(",");
  } else {
    return_string.concat(x);
    return_string.concat(",");
  }

  if (_axis_not_recorded(y)) {
    return_string.concat("NULL");
    return_string.concat(",");
  } else {
    return_string.concat(y);
    return_string.concat(",");
  }

  if (_axis_not_recorded(z)) {
    return_string.concat("NULL");
  } else {
    return_string.concat(z);
  }
  return return_string;
}

bool Acceleration::_axis_not_recorded(float axis) {
  if (axis == NOT_RECORDED) {
    return true;
  } else {
    return false;
  }
}
