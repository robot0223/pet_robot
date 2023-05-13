#include<Arduino.h>
#include<SoftwareSerial.h>
#include<Mecha_VoiceRecognition.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

int mota1 = 2; 
int mota2 = 3; 
int motb1 = 4; 
int motb2 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(mota1, OUTPUT);
  pinMode(motb1, OUTPUT);
  pinMode(mota2, OUTPUT);
  pinMode(motb2, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
}

int forward(int mot1speed,int mot2speed)
{
  analogWrite(mota1,mot1speed);
  analogWrite(motb1,mot2speed);
}
