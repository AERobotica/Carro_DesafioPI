#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "encoder.h"
#include "PID.h"
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
    unsigned long _tempo_espera;
    Encoder& _encoder;
    PID _PID_RPM;
public:
    Motor(int ENA, int IN1, int IN2, Encoder& encoder);
    void setpoint_perc(float setpoint);
    void setpoint_RPM(float setpoint_RPM);
    void setpoint_cm_per_s(float setpoint_cmpers);
};



#endif