/*************************************************************************
 * Master_Example.pde ----- Sample sketch for retrieving data from Slave_Example.pde
 * 
 * A sample sketch that shows of the master side for retrieving data
 * from the Slave_Example.pde sketch
 *
 * Copyright (c) 2011, DSS Circuits, Inc.  http://www.dsscircuits.com
 * 
 *************************************************************************/

#include <Wire.h>

byte i2cData[14];
byte test = 0;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
}

void loop()
{
  Wire.beginTransmission(0x29);
  Wire.send(0x00);
  Wire.endTransmission();
  Wire.requestFrom(0x29,14);
  for (int i = 0; i < 14; i++)
  {
    Serial.println(Wire.receive(),HEX);
  }
  delay(1000);
  Serial.println();
  Wire.beginTransmission(0x29);
  Wire.send(0x0B);
  Wire.send(test);
  Wire.send(test+1);
  Wire.endTransmission();
  test++;
}

