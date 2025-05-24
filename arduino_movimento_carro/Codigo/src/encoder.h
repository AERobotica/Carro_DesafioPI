
#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

/*####### MOTOR #######*/
//#define motor_yellow 2 //ENCA_motor
//#define motor_white 4 //ENCB_motor
//motor_blue  -> +5V
//motor_green -> GND

class Encoder
{
private:
    
    volatile long _passos_encoder;
    long _passos_encoder_last;
    unsigned long _tempo_last;
    unsigned long _distance_mm; // max de (2^32)-1 mm
    void add_distance(long delta_passos);
public:
    Encoder(int pin_yellow, int pin_white);
    int motor_yellow;
    int motor_white;
    void add_passos();
    void remove_passos();
    float get_RPM();
    float get_distance_m();
    uint16_t _perimetro_roda_mm = 365; 
};



#endif


