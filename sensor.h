#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
    virtual int readValue() const = 0;  // Méthode pure virtuelle, qui sera implementée par les classes dérivées
};

#endif // SENSOR_H
