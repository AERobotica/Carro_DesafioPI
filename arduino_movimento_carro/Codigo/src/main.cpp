#include <Arduino.h>
#include "encoder.h"
#include "motor.h"


unsigned tempo;
volatile long passos_encoder=0; //volatile para ser possivel alterar o valor fora do fluxo dito normal
long passos_encoder_last = 0;

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
  tempo = millis();
  attachInterrupt(digitalPinToInterrupt(encoder_frente_esq.motor_yellow),motor_frente_esq_read_encoder, RISING);
}

void loop() {
  if((millis() - tempo) > 5000){
    Serial.println("RPM: " + String(encoder_frente_esq.get_RPM()));
  }else if(millis() < tempo){
    tempo = millis();
  }
  
  motor_frente_esq.setpoint_RPM(100.0);

}