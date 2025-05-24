#include "motor.h"

Motor::Motor(int ENA, int IN1, int IN2, Encoder& encoder):_encoder(encoder), _PID_RPM(0.02,0.06,0.05)
{
    _ENA = ENA;
    _IN1 = IN1;
    _IN2 = IN2;
    pinMode(_ENA, OUTPUT);
    pinMode(_IN1, OUTPUT);
    pinMode(_IN2, OUTPUT);
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, LOW);
    _tempo_espera = millis();
}

void Motor::setpoint_perc(float setpoint)
{
    if(setpoint > 0){
        setpoint = (setpoint * 255.0)/100;
        digitalWrite(_IN1, HIGH);
        digitalWrite(_IN2, LOW);
        analogWrite(_ENA, setpoint);
        //Serial.println("setpoint: " + String(setpoint));
    }else if(setpoint < 0){
        setpoint = (-setpoint * 255.0)/100;
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, HIGH);
        analogWrite(_ENA, setpoint);
        //Serial.println("setpoint: " + String(setpoint));
    }else{
        analogWrite(_ENA, setpoint);
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, LOW);
        Serial.println("Motor parado");
    }
}

/**************************************************************************/
/*!
    @brief  Irá ler do encoder os RPM e utiliza um controlado PI para manter
    os RPM pretendidos. Valor de RPM máximo de 320 RPM.

    @return 
*/
/**************************************************************************/
void Motor::setpoint_RPM(float setpoint_RPM) //testar frente e para trás
{
    if((millis() - _tempo_espera >= 50) || ((millis() < _tempo_espera) && (((4294967295UL - _tempo_espera) + millis()) >= 50))){
        Serial.println("setpoint_RPM_colocado: " + String(setpoint_RPM) + " encoder_RPM: " + String(_encoder.get_RPM()));
        if(setpoint_RPM > 0){
            setpoint_RPM = _PID_RPM.controlador((float) setpoint_RPM, (float) _encoder.get_RPM());
            setpoint_RPM = (setpoint_RPM * 255.0)/100;
            digitalWrite(_IN1, LOW);
            digitalWrite(_IN2, HIGH);
            analogWrite(_ENA, setpoint_RPM);
            Serial.println("setpoint: " + String(setpoint_RPM));
        }else if(setpoint_RPM < 0){
            setpoint_RPM = _PID_RPM.controlador((float) -setpoint_RPM, (float) -_encoder.get_RPM());
            setpoint_RPM = (setpoint_RPM * 255.0)/100;
            digitalWrite(_IN1, HIGH);
            digitalWrite(_IN2, LOW);
            analogWrite(_ENA, setpoint_RPM);
            Serial.println("setpoint: " + String(setpoint_RPM));
        }else{
            analogWrite(_ENA, setpoint_RPM);
            digitalWrite(_IN1, LOW);
            digitalWrite(_IN2, LOW);
            Serial.println("Motor parado");
        }
        _tempo_espera = millis();
    }
}

void Motor::setpoint_cm_per_s(float setpoint_cmpers) 
{
    setpoint_cmpers = ((setpoint_cmpers * 60.0)*10.0)/((float)(_encoder._perimetro_roda_mm)); //passar para RPM
    setpoint_RPM(setpoint_cmpers);
}
