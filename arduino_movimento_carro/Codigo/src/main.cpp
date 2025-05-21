#include <Arduino.h>

/*####### MOTOR #######*/
#define motor_yellow 2 //ENCA_motor
#define motor_white 4 //ENCB_motor
//motor_blue  -> +5V
//motor_green -> GND

/*####### L298N - DRIVER ######*/
#define driver_ENA 5
#define driver_IN1 6
#define driver_IN2 7

unsigned tempo;
volatile long passos_encoder=0; //volatile para ser possivel alterar o valor fora do fluxo dito normal
long passos_encoder_last = 0;


void readEncoder(){
  if(digitalRead(motor_white) == 0){
    passos_encoder++;
  }else{
    passos_encoder--;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(motor_yellow, INPUT);
  pinMode(motor_white, INPUT);
  pinMode(driver_ENA, OUTPUT);
  pinMode(driver_IN1, OUTPUT);
  pinMode(driver_IN2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motor_yellow),readEncoder, RISING);
  tempo = millis();
}



void loop() {
  if((millis() - tempo) > 5000){
    // 1 volta completa = 64*30 = 1920 ticks
    float rotacoes = (float)(passos_encoder - passos_encoder_last)*4.0/1920.0;
    passos_encoder_last = passos_encoder;
    int delta_tempo = millis() - tempo;
    tempo = millis();
    float RPM = (rotacoes*1000.0*60.0)/((float)(delta_tempo));

    //Prevenção de overflow do passos_encoder
    if(passos_encoder > 2047483647){
      passos_encoder = 0;
      passos_encoder_last = 0;
    }else if(passos_encoder < -2047483647){
      passos_encoder = 0;
      passos_encoder_last = 0;
    }
    
    Serial.println("RPM: " + String(RPM) + " | Delta Tempo: " + String(delta_tempo) + " | Passos Encoder: " + passos_encoder + " | Rotações: " + rotacoes);
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




