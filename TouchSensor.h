#ifndef TOUCHSENSOR_H
#define TOUCHSENSOR_H

#include "sensor.h" 

class TouchSensor : public Sensor {
public:
    TouchSensor();
    ~TouchSensor();
    virtual int readValue() const override;  // Implémenter la méthode virtuelle de la classe de base
};

#endif 
