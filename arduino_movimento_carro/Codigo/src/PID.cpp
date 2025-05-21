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

uint16_t PID::controlador(float setpoint, float truepoint)
{
    //Controlador PI
  _atuacao = (_Kc + ((_Kc*_T)/(_Ti)))*_erro - _Kc*_erro_anterior + _atuacao_anterior;

  _erro_anterior = _erro;
  _atuacao_anterior = _atuacao;

  Serial.println("Erro: " + String(_erro) + " | Atuação: " + String(_atuacao));

  //atuacao de 0 a 100%
  if(_atuacao > 30){
    _atuacao = 30;
  }else if(_atuacao < 0){
    _atuacao = 0;
  }

  //passar de 0-100% para 0-1024
  _atuacao = (_atuacao*1024)/100;

  Serial.println("Atuação Filtrada: " + String(_atuacao));

  return _atuacao;

}