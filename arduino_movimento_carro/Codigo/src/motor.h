#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

/*
####### L298N - DRIVER ######
#define driver_ENA 5
#define driver_IN1 6
#define driver_IN2 7
*/

class Motor
{
private:
    int _ENA;
    int _IN1;
    int _IN2;
public:
    Motor(int ENA, int IN1, int IN2);
    void setpoint_perc(float setpoint);
};



#endif