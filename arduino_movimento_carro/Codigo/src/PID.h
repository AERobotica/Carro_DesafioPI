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
    unsigned long tempo_anterior;
    float _Kp;
    float _Ki;
    float _Kd;
    //float _Kc;
    float _delta_T;
    float _deriv_comp;
    float _integr_comp;
    //float _T;
    //float _Ti;
public:
    PID(float Kc, float Ti,float T);
    int16_t controlador(float setpoint, float truepoint, bool direcao_frente); 
};


#endif