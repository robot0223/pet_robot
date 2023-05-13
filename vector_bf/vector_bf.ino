//libraries
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Mecha_VoiceRecognition.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>
#include <Servo.h>
#include <HUSKYLENS.h>

//voice
SoftwareSerial uart_voice(10, 11);  //RX, TX
Mecha_VoiceRecognition voice(&uart_voice);

//tft lcd
#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

//hardware spi communication
Adafruit_ILI9340 tft = Adafruit_ILI9340(CS, DC, TFT_RST);

//Huskeylens
HUSKYLENS huskylens;
SoftwareSerial mySerial(, );               // RX, TX
void huskeylens_printResult(HUSKYLENSResult result);  //function definition


//servo moter
Servo serv;

//tft lcd pin
#define SCLK 52
#define MISO 50
#define MOSI 51
#define CS 53
#define DC 48
#define TFT_RST 49
#define TFTLED 6

//moter pin
#define MOTOR_A1 2
#define MOTOR_A2 3
#define MOTOR_B1 4
#define MOTOR_B2 5

//etc. pin



//voltage
#define TFT__V 120








void setup() {
  //Serial
  Serial.begin(9600);
  Serial.begin(115200);

  //pin settings
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
  pinMode(TFTLED, OUTPUT);
  
  //voice
  voice.setDebugOn(&Serial);
  voice.setGroup(VOICE_GROUP_1);
  voice.init();
  voice.setMode(VOICE_MODE_RECOGNITION);

  //servo
  //serv.attach(SERVO_MOTOR);


  //tft lcd
  analogWrite(TFTLED, TFT_V);
  tft.begin();
  tft.fillScreen(ILI9340_BLACK);
  Serial.println(closed_eye());
}

void loop() {
  //get voice memory
  VOICE_InstructionTypeDef response = voice.getInstruction();
  if (response == VOICE_INSTRUCTION_1 || response == VOICE_INSTRUCTION_2 || response == VOICE_INSTRUCTION_3 || response == VOICE_INSTRUCTION_4 || response == VOICE_INSTRUCTION_5) {
   //call function related to 'voicedetact-reaction'
  }





}


//dc motor movement functions
void forward(int mot1speed, int mot2speed) {
  analogWrite(MOTOR_A1, mot1speed);
  analogWrite(MOTOR_B1, mot2speed);
}

void backwards(int mot1speed, int mot2speed) {
analogWrite(MOTOR_A2);
analogWrite(MOTOR_B2);
}

void leftspin(int mot1speed, int mot2speed){
analogWrite(MOTOR_A2);
analogWrite(MOTOR_B1);
}

void rightspin(int mot1speed, int mot2speed){
analogWrite(MOTOR_A1);
analogWrite(MOTOR_B2);
}



//huskeylens functions
void huskeylens_printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  } else {
    Serial.println("Object unknown!");
  }
}



// tft lcd functions
unsigned long eye() {
  tft.fillRoundRect(50, 40, 100, 100, 30, tft.Color565(0, 100, 0));//tft.Color565(red,green,blue);
  tft.fillRoundRect(50, 180, 100, 100, 30, tft.Color565(0, 100, 0));
  tft.fillRoundRect(50, 40, 95, 95, 30, tft.Color565(0, 150, 0));
  tft.fillRoundRect(50, 180, 95, 95, 30, tft.Color565(0, 150, 0));
  tft.fillRoundRect(55, 45, 90, 90, 30, tft.Color565(0, 240, 0));
  tft.fillRoundRect(55, 185, 90, 90, 30, tft.Color565(0, 240, 0));
}



unsigned long closed_eye() {
  tft.fillRoundRect(55, 45, 90, 90, 30, tft.Color565(0, 0, 0));
  tft.fillRoundRect(55, 185, 90, 90, 30, tft.Color565(0, 0, 0));
  tft.fillRoundRect(50, 40, 90, 90, 30, tft.Color565(0, 240, 0));
  tft.fillRoundRect(50, 180, 90, 90, 30, tft.Color565(0, 240, 0));
}





