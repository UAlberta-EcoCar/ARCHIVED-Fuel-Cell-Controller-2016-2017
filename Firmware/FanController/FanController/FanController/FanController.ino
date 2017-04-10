#include <Arduino.h>
#include <Wire.h>

#include "Pin_Defines.h"
#include "ThermistorLookup.h"

#define SLAVE_ADDRESS 0x02


uint8_t Reg = 0;
//bit   function
//1     mos_1
//2     mos_2
//3     mos_3

char temp[2];

void setup() {
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  Serial.println("Starting");

  pinMode(THERM1,INPUT);
  pinMode(THERM2,INPUT);

  pinMode(MOS_1,OUTPUT);
  pinMode(MOS_2,OUTPUT);
  pinMode(MOS_3,OUTPUT);

  pinMode(13,OUTPUT);
}

void loop() {
  temp[0] = analogRead(THERM1);
  temp[1] = analogRead(THERM2);

  float temperature = ((float)temp[0] + (float)temp[1])/2;
  temperature = therm_lookup(temperature/5.0f);

  if(temperature>32.0f)
  {
    analogWrite(PWM_1,255);
    analogWrite(PWM_2,255);
    analogWrite(PWM_3,255);
  }
  else
  {
    analogWrite(PWM_1,30);
    analogWrite(PWM_2,30);
    analogWrite(PWM_3,30);
  }

  if(Reg)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  if(Reg&(1<<0))
  {
    digitalWrite(MOS_1,HIGH);
  }
  else
  {
    digitalWrite(MOS_1,LOW);
  }
  if(Reg&(2<<0))
  {
    digitalWrite(MOS_2,HIGH);
  }
  else
  {
    digitalWrite(MOS_2,LOW);
  }
  if(Reg&(3<<0))
  {
    digitalWrite(MOS_3,HIGH);
  }
  else
  {
    digitalWrite(MOS_3,LOW);
  }
}

void requestEvent()
{
  //insert data you want to send here
  Wire.write(temp,2);
  Serial.println("data sent");
}

void receiveEvent(int bytesReceived)
{
  Reg = Wire.read();
  Serial.println("data received");
  Serial.println(Reg);
}
