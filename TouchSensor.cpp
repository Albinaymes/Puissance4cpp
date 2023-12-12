#include "TouchSensor.h"
#include <Arduino.h>

//le touch sensor est ici plug sur la pin D8
TouchSensor::TouchSensor() {}

TouchSensor::~TouchSensor() {}

int TouchSensor::readValue() const {
  return digitalRead(D8);
}