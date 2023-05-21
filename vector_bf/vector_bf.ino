//libraries
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Mecha_VoiceRecognition.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>
#include <Servo.h>
#include <HUSKYLENS.h>

//voice pin
#define VOICE_RX 10
#define VOICE_TX 11

//bluetooth pin
#define BLUETOOTH_RX 14
#define BLUETOOTH_TX 15

//huskeylens pin
#define HUSKEYLENS_RX 12
#define HUSKEYLENS_TX 13
//tft lcd pin
#define SCLK 52
#define MISO 50
#define MOSI 51
#define CS 53
#define DC 48
#define TFT_RST 49
#define TFT_LED 6

//moter pin
#define MOTOR_A1 2
#define MOTOR_A2 3
#define MOTOR_B1 4
#define MOTOR_B2 5
#define SERVO 24
//etc. pin
#define BUZZER 22
#define BUTTON 23


//voltage
#define TFT_V 120
#define V_0 0


//values
int enable_main;




//voice
SoftwareSerial uart_voice(VOICE_RX, VOICE_TX);  //RX, TX
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
SoftwareSerial mySerial(, );  // RX, TX

//servo moter
Servo serv;

//bluetooth
SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);


void setup() {
  //Serial
  Serial.begin(9600);
  Serial.begin(115200);

  //pin settings
  //dc motor
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);

  //tft lcd
  pinMode(TFTLED, OUTPUT);


  //etcf.
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  //voice
  voice.setDebugOn(&Serial);
  voice.setGroup(VOICE_GROUP_1);
  voice.init();
  voice.setMode(VOICE_MODE_RECOGNITION);

  //servo
  serv.attach(SERVO);  //servo definition (just to remind that servo needs to be set)
  //detach in order to conserve energy
  serv.detach();

  //tft lcd basic use
  /*analogWrite(TFT_LED, TFT_V);
  tft.begin();
  tft.fillScreen(ILI9340_BLACK);
  Serial.println(closed_eye());
  */
}

void loop() {
  int button_input = digitalRead(BUTTON);
  //if button is pressed
  if (button_input == 1) {
    //turn robot into wake mode(servo on, lcd on)
    robot_wake();

    //lcd print download robot app
    //if connected lcd print connected
    robot_start();
    //enable main mode
    enable_main = 1;
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

void leftspin(int mot1speed, int mot2speed) {
  analogWrite(MOTOR_A2);
  analogWrite(MOTOR_B1);
}

void rightspin(int mot1speed, int mot2speed) {
  analogWrite(MOTOR_A1);
  analogWrite(MOTOR_B2);
}

//voice recongniton functions
void voicerecongnition_response() {
  VOICE_InstructionTypeDef response = voice.getInstruction();
  if (response == VOICE_INSTRUCTION_1 || response == VOICE_INSTRUCTION_2 || response == VOICE_INSTRUCTION_3 || response == VOICE_INSTRUCTION_4 || response == VOICE_INSTRUCTION_5) {

    voice.setGroup(VOICE_GROUP_2);
    VOICE_InstructionTypeDef response = voice.getInstruction();

    switch (response) {
      case VOICE_INSTRUCTION_1:
        Serial.println("1");
        break;
    }
  }
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
  tft.fillRoundRect(50, 40, 100, 100, 30, tft.Color565(0, 100, 0));  //tft.Color565(red,green,blue);
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



//robot on->off control functions
void robot_wake() {
  serv.attach(SERVO);
  analogWrite(TFT_LED, TFT_V);
}

void robot_sleep() {
  serv.detach();
  ananlogWrite(TFT_LED, V_0);
}

void robot_start() {
  //lcd print download robot app
  tft.fillScreen(ILI9340_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9340_WHITE);
  tft.setTextSize(1);
  tft.println("DOWNLOAD PET_ROBOT APP");
  //if connected lcd print connected
  if (bluetooth.available()) {
    tft.fillScreen(ILI9340_BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(ILI9340_WHITE);
    tft.setTextSize(1);
    tft.println("bluetooth conncetion complet.");
  }
}
