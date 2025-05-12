#include <Arduino.h>

#define motor_yellow 2 //ENCA
#define motor_white 3 //ENCB
//motor_blue  -> +5V
//motor_green -> GND


void setup() {
  Serial.begin(9600);
  pinMode(motor_yellow, INPUT);
  pinMode(motor_white, INPUT);
}

void loop() {
  int a  = digitalRead(motor_yellow);
  int b  = digitalRead(motor_white);
  Serial.println(String(a) + " " + String(b));
}

