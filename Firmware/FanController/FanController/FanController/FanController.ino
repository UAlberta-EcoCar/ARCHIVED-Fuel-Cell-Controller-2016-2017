#include <Arduino.h>
#include <Wire.h>

#include "Pin_Defines.h"
#include "ThermistorLookup.h"

#define SLAVE_ADDRESS 0x05

uint8_t Reg = 0;

//bit   function
//3     mos_3

uint8_t temp[3];

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  pinMode(THERM1,INPUT);
  
  pinMode(MOS_3,OUTPUT);

  analogReference(DEFAULT);
}

int pwr;

float i = 0;
long timer = 0;

float setpoint = 32.0f;

void loop() {
  digitalWrite(MOS_3,HIGH);
  int T = analogRead(THERM1);
  temp[0] = T/4;
  temp[1] = T&0b11;

  float temperature = (float)T;
  temperature = therm_lookup(temperature/1023.0f);

  float p = (temperature - setpoint)*25;
  if(p < 0)
  {
    p = 0;
  }

  if(millis()-timer>100)
  {
    i += (temperature -setpoint)*0.1;
    timer = millis();
  }

  if(i>120.0)
  {
    i = 120.0;
  }
  if(i<-120.0)
  {
    i = -120.0;
  }

  pwr = (int)p + (int)i;

  if(pwr <= 10)
  {
    pwr = 10;
  }
  if(pwr > 255)
  {
    pwr = 255;
  }
  if(1)
  {
    temp[2] = (uint8_t)pwr;
  }
  else
  {
    temp[2] = 0;
  }

  //Reg = 1<<3;
  //if(Reg&(3<<0))
  //{
    digitalWrite(MOS_3,HIGH);
  //}
  //else
  //{
   // digitalWrite(MOS_3,LOW);
  //}

  analogWrite(PWM_3,pwr);
  
}

void requestEvent()
{
  //insert data you want to send here
  Wire.write(temp,3);
}

void receiveEvent(int bytesReceived)
{
  Reg = Wire.read();
}
