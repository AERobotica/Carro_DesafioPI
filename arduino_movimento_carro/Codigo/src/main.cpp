#include <Arduino.h>
#include "encoder.h"

/*####### L298N - DRIVER ######*/
#define driver_ENA 5
#define driver_IN1 6
#define driver_IN2 7

unsigned tempo;
volatile long passos_encoder=0; //volatile para ser possivel alterar o valor fora do fluxo dito normal
long passos_encoder_last = 0;

Encoder motor_frente_esq(2, 4);

void motor_frente_esq_read_encoder(){
  if(digitalRead(motor_frente_esq.motor_white) == 0){
    motor_frente_esq.add_passos();
  }else{
    motor_frente_esq.remove_passos();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(driver_ENA, OUTPUT);
  pinMode(driver_IN1, OUTPUT);
  pinMode(driver_IN2, OUTPUT);
  tempo = millis();
  attachInterrupt(digitalPinToInterrupt(motor_frente_esq.motor_yellow),motor_frente_esq_read_encoder, RISING);
}



void loop() {
  if((millis() - tempo) > 5000){
   motor_frente_esq.get_RPM();
  }else if(millis() < tempo){
    tempo = millis();
  }


  analogWrite(driver_ENA, 0);
  digitalWrite(driver_IN1, LOW);
  digitalWrite(driver_IN2, HIGH);
  delay(1500);
  
  analogWrite(driver_ENA, 50);
  delay(1500);

  analogWrite(driver_ENA, 100);
  delay(1500);

  analogWrite(driver_ENA, 150);
  delay(1500);
}




