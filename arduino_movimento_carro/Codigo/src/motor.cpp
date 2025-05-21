#include "motor.h"

Motor::Motor(int ENA, int IN1, int IN2)
{
    _ENA = ENA;
    _IN1 = IN1;
    _IN2 = IN2;
    pinMode(_ENA, OUTPUT);
    pinMode(_IN1, OUTPUT);
    pinMode(_IN2, OUTPUT);
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, LOW);
}

void Motor::setpoint_perc(float setpoint)
{
    if(setpoint > 0){
        setpoint = (setpoint * 255.0)/100;
        digitalWrite(_IN1, HIGH);
        digitalWrite(_IN2, LOW);
        analogWrite(_ENA, setpoint);
        Serial.println("setpoint: " + String(setpoint));
    }else if(setpoint < 0){
        setpoint = (-setpoint * 255.0)/100;
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, HIGH);
        analogWrite(_ENA, setpoint);
        Serial.println("setpoint: " + String(setpoint));
    }else{
        analogWrite(_ENA, setpoint);
        digitalWrite(_IN1, LOW);
        digitalWrite(_IN2, LOW);
        Serial.println("Motor parado");
    }
}
