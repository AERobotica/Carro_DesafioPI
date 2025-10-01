#include <Arduino.h>
#include "encoder.h"
#include "motor.h"


#define Enconder_Yellow_frente_esq 2
#define Enconder_White_frente_esq 4
#define ENA_frente_esq_PWM 6
#define INA1_frente_esq 12
#define INA2_frente_esq 9


#define Enconder_Yellow_frente_dir 3
#define Enconder_White_frente_dir 5
#define ENA_frente_dir_PWM 10
#define INA3_frente_dir 13
#define INA4_frente_dir 11


unsigned long tempo;

Encoder encoder_frente_esq(Enconder_Yellow_frente_esq, Enconder_White_frente_esq);
Motor   motor_frente_esq(ENA_frente_esq_PWM, INA1_frente_esq, INA2_frente_esq,  encoder_frente_esq);

Encoder encoder_frente_dir(Enconder_Yellow_frente_dir, Enconder_White_frente_dir);
Motor   motor_frente_dir(ENA_frente_dir_PWM, INA3_frente_dir, INA4_frente_dir, encoder_frente_dir);


void motor_frente_esq_read_encoder(){
  if(digitalRead(encoder_frente_esq.motor_white) == 0){
    encoder_frente_esq.add_passos();
  }else{
    encoder_frente_esq.remove_passos();
  }
}

void motor_frente_dir_read_encoder(){
  if(digitalRead(encoder_frente_dir.motor_white) == 0){
    encoder_frente_dir.add_passos();
  }else{
    encoder_frente_dir.remove_passos();
  }
}

void setup() {
  Serial.begin(115200);
  tempo = micros();
  attachInterrupt(digitalPinToInterrupt(encoder_frente_esq.motor_yellow),motor_frente_esq_read_encoder, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder_frente_dir.motor_yellow),motor_frente_dir_read_encoder, RISING);
}

void loop() {

 
  //while(micros() - tempo < 5000000){
    
  
  motor_frente_esq.setpoint_RPM(100.0);
  motor_frente_dir.setpoint_RPM(100.0);
  Serial.println(">RPM_esq:" + String(encoder_frente_esq.get_RPM()));
  Serial.println(">distancia_esq:" + String(encoder_frente_esq.get_distance_m()));
  Serial.println(">atuacao_esq:" + String(motor_frente_esq._PID_RPM._atuacao));

  Serial.println(">RPM_dir:" + String(encoder_frente_dir.get_RPM()));
  Serial.println(">distancia_dir:" + String(encoder_frente_dir.get_distance_m()));
  Serial.println(">atuacao_dir:" + String(motor_frente_dir._PID_RPM._atuacao));
  //tempo = micros();
  
  
  //Serial.println(">atuacao_esq:" + String(motor_frente_esq._PID_RPM._atuacao));
  //}
 

}
