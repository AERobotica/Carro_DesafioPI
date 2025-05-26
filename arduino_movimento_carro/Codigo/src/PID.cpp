#include "PID.h"

PID::PID(float Kc, float Ti, float T_s)//T_s em segundos
{
    if(Kc >= 0){
        _Kc = Kc;
    }else{
        Serial.println("O valor Kc não pode ser negativo");
        _Kc=0;
    }
    if(Ti >= 0){
        _Ti = Ti;
    }else{
        Serial.println("O valor Ti não pode ser negativo");
        _Ti=0;
    }
    if(T_s > 0){
        _T = T_s;
    }else{
        Serial.println("O valor T não pode ser negativo ou 0. T = 1s");
        _T=1;
    }
    _erro_anterior = 0;
    _atuacao_anterior = 0;
}

int16_t PID::controlador(float setpoint, float truepoint, bool direcao)
{
    //Serial.println("erro: " + String(setpoint - truepoint));
    _erro = setpoint - truepoint;
    //Controlador PI
  _atuacao = (_Kc + ((_Kc*_T)/(_Ti)))*_erro - _Kc*_erro_anterior + _atuacao_anterior;

  _erro_anterior = _erro;
  _atuacao_anterior = _atuacao;

  //Serial.println("Erro: " + String(_erro) + " | Atuação: " + String(_atuacao));
  //Serial.println("Kc:" + String(_Kc) + "_T:" + String(_T) + "_Ti:" + String(_Ti));
  //atuacao de 0 a 100%
  if(direcao){
    if(_atuacao > 255){
    _atuacao = 255;
  }else if(_atuacao < 0){
    _atuacao = 0;
  }
  }else{
    if(_atuacao > 0){
    _atuacao = 0;
  }else if(_atuacao <-255){
    _atuacao = -255;
  }
  }
  
  //Serial.println("Atuação Filtrada: " + String(_atuacao));

  return _atuacao;

}