#include "encoder.h"

void Encoder::add_distance(long delta_passos)
{
  _distance_mm =+ (delta_passos*_perimetro_roda_mm)/480;
}

Encoder::Encoder(int pin_yellow, int pin_white)
{   motor_white = pin_white;
    motor_yellow = pin_yellow;
    pinMode(motor_yellow, INPUT);
    pinMode(motor_white, INPUT);
    _passos_encoder = 0;
    _passos_encoder_last = 0;
    _tempo_last = micros();
    
}

void Encoder::remove_passos()
{
    _passos_encoder--;
}

float Encoder::get_RPM()
{
     
    long delta_passos = _passos_encoder - _passos_encoder_last;
     _passos_encoder_last = _passos_encoder;
    unsigned long delta_tempo = 1;
    if(micros() >= _tempo_last){
        //Serial.println("tempo_last: " + String(_tempo_last) + " micros: " + String(micros()));
        delta_tempo = micros() - _tempo_last;    
    }else{
        delta_tempo = (4294967295UL - _tempo_last) + micros(); 
    }
    // 1 volta completa = 64*30 = 1920 ticks
    add_distance(delta_passos);
    float rotacoes = (float)(delta_passos)*4/1920.0; //não sei pq é preciso o x4

    //Serial.println("delta_tempo: " + String(delta_tempo) + " rotações: " + String(rotacoes*100));
    if(delta_tempo == 0){
        return 0.0;
    }

    float RPM = (rotacoes*1000000.0*60.0)/((float)(delta_tempo));
    _tempo_last = micros();
    
    //Prevenção de overflow do _passos_encoder
    if(_passos_encoder > 2047483647){
      _passos_encoder = 0;
      _passos_encoder_last = 0;
    }else if(_passos_encoder < -2047483647){
      _passos_encoder = 0;
      _passos_encoder_last = 0;
    }
    return RPM;
}

float Encoder::get_distance_m()
{
    return (float)_distance_mm/1000;
}

void Encoder::add_passos()
{
    _passos_encoder++;
}
