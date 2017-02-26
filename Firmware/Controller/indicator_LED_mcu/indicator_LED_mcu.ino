#include <Arduino.h>
#include <Wire.h>

#include "Pin_Defines.h"

#define SLAVE_ADDRESS 0x01

uint16_t Reg = 0;

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  //pinMode(LED5,OUTPUT);
  //pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(LED8,OUTPUT);
  pinMode(LED9,OUTPUT);
  pinMode(LED10,OUTPUT);
  pinMode(LED11,OUTPUT);
  pinMode(LED12,OUTPUT);

  pinMode(13,OUTPUT);
}

void loop() {
  if(bitRead(Reg,0))
  {
    digitalWrite(LED1,HIGH);
  }
  else
  {
    digitalWrite(LED1,LOW);
  }
  if(bitRead(Reg,1))
  {
    digitalWrite(LED2,HIGH);
  }
  else
  {
    digitalWrite(LED2,LOW);
  }
  if(bitRead(Reg,2))
  {
    digitalWrite(LED3,HIGH);
  }
  else
  {
    digitalWrite(LED3,LOW);
  }
  if(bitRead(Reg,3))
  {
    digitalWrite(LED4,HIGH);
  }
  else
  {
    digitalWrite(LED4,LOW);
  }
  if(bitRead(Reg,6))
  {
    digitalWrite(LED7,HIGH);
  }
  else
  {
    digitalWrite(LED7,LOW);
  }
  if(bitRead(Reg,7))
  {
    digitalWrite(LED8,HIGH);
  }
  else
  {
    digitalWrite(LED8,LOW);
  }
  if(bitRead(Reg,8))
  {
    digitalWrite(LED9,HIGH);
  }
  else
  {
    digitalWrite(LED9,LOW);
  }
  if(bitRead(Reg,9))
  {
    digitalWrite(LED10,HIGH);
  }
  else
  {
    digitalWrite(LED10,LOW);
  }
  if(bitRead(Reg,10))
  {
    digitalWrite(LED11,HIGH);
  }
  else
  {
    digitalWrite(LED11,LOW);
  }
  if(bitRead(Reg,11))
  {
    digitalWrite(LED12,HIGH);
  }
  else
  {
    digitalWrite(LED12,LOW);
  }
  if(bitRead(Reg,12))
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
}

void requestEvent()
{
  //insert data you want to send here
//  char data[2];
//  data[0] = 0xAB;
//  data[1] = 0xCD;
//  Wire.write(data,2);
}

void receiveEvent(int bytesReceived)
{
  Reg = 0;
  for (int a = 0;a<bytesReceived;a++)
  {
    //first byte
    if(a == 0)
    {
      Reg = Wire.read();
    }
    //second byte
    else if(a == 1)
    {
      Reg |= Wire.read() << 8;
    }
    //anything else
    else
    {
      Wire.read();
    }
  }
}

