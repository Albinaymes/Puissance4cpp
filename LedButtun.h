#ifndef LEDBUTTUN_H
#define LEDBUTTUN_H

#include "sensor.h"  

class LedButtun : public Sensor {
public:
    LedButtun();
    ~LedButtun();
    virtual int readValue() const override;  
    void allumerLed();
    void eteindreLed();
};

#endif 
