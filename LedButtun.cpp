#include "LedButtun.h"
#include <Arduino.h>

//Bouton led branché sur le D3 (bouton sur D5 et led sur D3)

LedButtun::LedButtun() {}

LedButtun::~LedButtun() {}

int LedButtun::readValue() const {
  return digitalRead(D5);
}

void  LedButtun::allumerLed(){
  digitalWrite(D3,HIGH);
}

void  LedButtun::eteindreLed(){
  digitalWrite(D3,LOW);
}