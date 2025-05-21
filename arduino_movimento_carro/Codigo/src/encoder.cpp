#include "encoder.h"



Encoder::Encoder(int pin_yellow, int pin_white)
{   motor_white = pin_white;
    motor_yellow = pin_yellow;
    pinMode(motor_yellow, INPUT);
    pinMode(motor_white, INPUT);
    _passos_encoder = 0;
    _passos_encoder_last = 0;
    _tempo_last = millis();
    
}

void Encoder::remove_passos()
{
    _passos_encoder--;
}

float Encoder::get_RPM()
{
     // 1 volta completa = 64*30 = 1920 ticks
    float rotacoes = (float)(_passos_encoder - _passos_encoder_last)*4.0/1920.0; //não sei pq é preciso o x4
    _passos_encoder_last = _passos_encoder;
    unsigned int delta_tempo = 1;
    if(millis() >= _tempo_last){
         delta_tempo = millis() - _tempo_last;    
    }else{
        delta_tempo = (4294967295UL - _tempo_last) + millis(); 
    }

    //Serial.println("delta_tempo: " + String(delta_tempo));
    if(delta_tempo == 0){
        return 0.0;
    }

    float RPM = (rotacoes*1000.0*60.0)/((float)(delta_tempo));
    _tempo_last = millis();
    
    //Prevenção de overflow do passos_encoder
    if(_passos_encoder > 2047483647){
      _passos_encoder = 0;
      _passos_encoder_last = 0;
    }else if(_passos_encoder < -2047483647){
      _passos_encoder = 0;
      _passos_encoder_last = 0;
    }
    return RPM;
}

void Encoder::add_passos()
{
    _passos_encoder++;
}
