#include <Arduino.h>
#include "encoder.h"
#include "motor.h"


unsigned long tempo;

Encoder encoder_frente_esq(2, 4);
Motor   motor_frente_esq(5,6,7, encoder_frente_esq);

void motor_frente_esq_read_encoder(){
  if(digitalRead(encoder_frente_esq.motor_white) == 0){
    encoder_frente_esq.add_passos();
  }else{
    encoder_frente_esq.remove_passos();
  }
}

void setup() {
  Serial.begin(9600);
  tempo = micros();
  attachInterrupt(digitalPinToInterrupt(encoder_frente_esq.motor_yellow),motor_frente_esq_read_encoder, RISING);
}

void loop() {

  
  
  while(micros() - tempo < 5000000){
    
  
  motor_frente_esq.setpoint_RPM(-50.0);
  }
  tempo = micros();
  while(micros() - tempo < 5000000){
    
  
  motor_frente_esq.setpoint_RPM(50.0);
  }
  tempo = micros();

}