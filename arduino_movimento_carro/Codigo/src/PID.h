#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID
{
private:
    float _erro;
    float _erro_anterior;
    float _atuacao;
    float _atuacao_anterior;
    float _Kc;
    float _T;
    float _Ti;
public:
    PID(float Kc, float Ti,float T);
    uint16_t controlador(float setpoint, float truepoint); 
};


#endif