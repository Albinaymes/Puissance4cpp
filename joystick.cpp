#include <Arduino.h>
#include "joystick.h"


joystick::joystick(){}

joystick::~joystick(){}

int joystick::readValue() const {
  return analogRead(A0);
}

int joystick::directionJoy(){
  int joystickValue = analogRead(A0);

  int middleValue = 535; // Valeur lue au milieu
  int tolerance = 100;    // Tolérance pour considérer que le joystick est centré
  int retour =0;   // retourne 0 si milieu, 1 si droite et 2 si gauche

  if (joystickValue < middleValue - tolerance) {
    retour=2;
  } else if (joystickValue > middleValue + tolerance) {
    retour=1;
  } else {
    retour=0;
  }
  return retour;
  

}