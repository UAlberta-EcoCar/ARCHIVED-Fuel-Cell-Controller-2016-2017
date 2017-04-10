#include <Arduino.h>
#include <Wire.h>

#include "Pin_Defines.h"
#include "commands.h"

#define SLAVE_ADDRESS 0x03

char read_data[25];

uint32_t timer = 0;

void setup() {
  Serial.begin(115200);
  //Wire.begin(SLAVE_ADDRESS);
  //Wire.onRequest(requestEvent);
  //Wire.onReceive(receiveEvent);
  timer = millis();
}

int motor_current;
int battery_current;
int battery_volts;
int encoder_rpm;
int encoder_count;
int motor_time;

#define READ_BUFF_SIZE 30
char read_buff[READ_BUFF_SIZE];
#define SECONDARY_BUFF_SIZE 8
char secondary_buff[SECONDARY_BUFF_SIZE];

uint8_t x = 0;

void loop() {
  read_data[0] = 0x01;
  read_data[1] = 0x03;
  delay(50);
  
  switch(read_data[0]) {
    case SET_DUTY_CYCLE :
      switch(read_data[1]) {
        case DUTY_CYCLE_ZERO :
          Serial.print("!G 1 0\r");
          break;
        case DUTY_CYCLE_200 :
          Serial.print("!G 1 200\r");
          break;
        case DUTY_CYCLE_300 :
          Serial.print("!G 1 300\r");
          break;
        case DUTY_CYCLE_400 :
          Serial.print("!G 1 400\r");
          break;
        case DUTY_CYCLE_500 :
          Serial.print("!G 1 500\r");
          break;
        case DUTY_CYCLE_600 :
          Serial.print("!G 1 600\r");
          break;
        case DUTY_CYCLE_700 :
          Serial.print("!G 1 700\r");
          break;
        case DUTY_CYCLE_800 :
          Serial.print("!G 1 800\r");
          break;
        case DUTY_CYCLE_900 :
          Serial.print("!G 1 900\r");
          break;
        case DUTY_CYCLE_1000 :
          Serial.print("!G 1 1000\r");
          break;
      }
      case EMERGENCY_STOP:
        Serial.print("!EX\r");
        break;
      case EMERGENCY_STOP_RELEASE:
        Serial.print("!MG\r");
        break;
      case START_SCRIPT:
        Serial.print("!R 0\r");
        break;
      case STOP_SCRIPT:
        Serial.print("!R 1\r");
        break;
      case RESTART_SCRIPT:
        Serial.print("!R 2\r");
        break;
      read_data[1] = 0;
      break;
  }
  read_data[0] = 0;

  if (millis() - timer > 250)
  {
    //flush serial buffer
//    while(Serial.available() > 0){
//      char t = Serial.read(); 
//    }
//    //read motor current
//    Serial.print("?A 1\r");
//    //read battery currnet
//    Serial.print("?BA 1\r");
//    //read internal volts
//    Serial.print("?V 1\r");
//    //read battery volts
//    Serial.print("?V 2\r");
//    //read encoder rpm
//    Serial.print("?S 1\r");
//    //read encoder count
//    Serial.print("?C 1\r");
//    //read time in seconds
//    Serial.print("?TM 1\r");
    
    timer = millis();
  }
}

char send_data[2];
void requestEvent()
{
  //insert data you want to send here
  send_data[0] = (char)(motor_current&0xFF);
  send_data[1] = (char)((motor_current>>8)&0xFF);

  send_data[4] = (battery_volts&0xFF);
  send_data[5] = ((battery_volts>>8)&0xFF);

  Wire.write(send_data,6);
}

void receiveEvent(int bytesReceived)
{
  for (int a = 0;a<bytesReceived;a++)
  {
    read_data[a] = Wire.read();
  }
}
