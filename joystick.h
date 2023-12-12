#ifndef JOYSTICK_H
#define JOYSTICK_H

class joystick{
  public :
  
  joystick();
  ~joystick();
  int readValue() const;
  int directionJoy();

};



#endif