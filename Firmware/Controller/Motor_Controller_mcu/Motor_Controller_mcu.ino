#include <Arduino.h>
#include <Wire.h>

#include "Pin_Defines.h"
#include "commands.h"

#define SLAVE_ADDRESS 0x03

uint8_t find_c(char * 

char read_data[25];

uint32_t timer = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
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

  switch(read_data[0]) {
    case SET_DUTY_CYCLE :
      switch(read_data[1]) {
        case DUTY_CYCLE_ZERO :
          Serial.print("!G 1 0\r");
          break;
        case DUTY_CYCLE_200 :
          Serial.print("!G 1 200\r");
          break;
        case DUTY_CYCLE_500 :
          Serial.print("!G 1 500\r");
          break;
      }
      read_data[1] = 0;
      break;
  }
  read_data[0] = 0;

  if (millis() - timer > 250)
  {
    //flush serial buffer
    while(Serial.available() > 0){
      char t = Serial.read(); 
    }
    //read battery volts
    Serial.print("?V 2\r");
    x = 0;
    //read string response from controller
    while(Serial.available() > 0){
      read_buff[x] = Serial.read();
      x++;
    }
    while(x < READ_BUFF_SIZE)
    {
      read_buff[x] = NULL;
      x++;
    }
//    x = 0;
//    while(read_buff[x] != '=')
//    {
//      x++;
//    }
//    x++;
//    //x++;
//    uint8_t y = 0;
//    while(read_buff[x] != NULL)
//    {
//      secondary_buff[y] = read_buff[x];
//      x++;
//      y++;
//    }
//    while(y < SECONDARY_BUFF_SIZE)
//    {
//      secondary_buff[y] = NULL;
//      y++;
//    }
//    String str = String(secondary_buff);
//    battery_volts =  str.toInt();
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
