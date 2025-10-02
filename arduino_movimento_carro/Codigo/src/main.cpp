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

 
   //verificar se existe algo no serial
  if(Serial.available() > 0){
    //ler a string até linha abaixo
    String input = Serial.readStringUntil('\n');
    //retirar espaços
    input.trim();

    int index_equal = input.indexOf('=');

    //verificar unidade composto por "unidade.funçao"
    if(index_equal != -1 && input.length() - 1){
      String comando = input.substring(0,index_equal-1);
      
      int index_unidade = input.indexOf('.');
      if(index_unidade != -1){
        String unidade = input.substring(0,index_unidade);
        String funcao = input.substring(index_unidade + 1, index_equal);
        float atuacao = input.substring(index_equal + 1, input.length()).toFloat(); 
        if( unidade == "motor_frente_esq"){
          if(funcao == "setpoint_perc"){
            Serial.println(atuacao);
            motor_frente_esq.setpoint_perc(atuacao);
          }
          else if(funcao == "setpoint_RPM"){
            motor_frente_esq.setpoint_RPM(atuacao);
          }
          else if(funcao == "setpoint_cm_per_s"){
            motor_frente_esq.setpoint_cm_per_s(atuacao);
          }
        }
        else if (unidade == "motor_frente_dir"){
          Serial.println("Entrou");
          Serial.println(funcao);
          if(funcao == "setpoint_perc"){
            motor_frente_dir.setpoint_perc(atuacao);
          }
          else if(funcao == "setpoint_RPM"){
            motor_frente_dir.setpoint_RPM(atuacao);
          }
          else if(funcao == "setpoint_cm_per_s"){
            motor_frente_dir.setpoint_cm_per_s(atuacao);
          }
        }
        else if (unidade == "encoder_frente_esq"){
          if(funcao == "get_distance_m"){
            encoder_frente_esq.get_distance_m(); //mandar via serial
          }
          else if(funcao == "get_RPM"){
            encoder_frente_esq.get_RPM();
          }
        }
        else if (unidade == "encoder_frente_dir"){
          if(funcao == "get_distance_m"){
            encoder_frente_dir.get_distance_m(); //mandar via serial
          }
          else if(funcao == "get_RPM"){
            encoder_frente_dir.get_RPM();
          }
        }
        
        
      }
    }

  }
  
  //while(micros() - tempo < 5000000){
  
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
