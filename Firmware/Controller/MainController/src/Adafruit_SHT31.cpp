/***************************************************
  This is a library for the SHT31 Digital Humidity & Temp Sensor

  Designed specifically to work with the SHT31 Digital sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "mbed.h"
#include "rtos.h"

#include "Adafruit_SHT31.h"

I2C i2c(I2C_SDA,I2C_SCL);

void sht31_reset(void)
{
  sht31_writeCommand(SHT31_SOFTRESET);
  Thread::wait(10);
}

void sht31_heater(bool h)
{
  if(h)
  {
    sht31_writeCommand(SHT31_HEATEREN);
    Thread::wait(10);
  }
  else
  {
    sht31_writeCommand(SHT31_HEATERDIS);
  }
}

float temp;

float sht31_readTemperature(void)
{
  if (! sht31_readTempHum()) return NAN;

  return temp;
}

float humidity;

float sht31_readHumidity(void)
{
  return humidity;
}


bool sht31_readTempHum(void)
{
  char readbuffer[6];
  
  sht31_writeCommand(SHT31_MEAS_HIGHREP);

  wait(0.5);

  i2c.read(SHT31_DEFAULT_ADDR<<1,readbuffer,6); //i2c returns a signed array

  uint16_t ST, SRH;
  ST = readbuffer[0];
  ST <<= 8;
  ST |= readbuffer[1];

//  if (readbuffer[2] != crc8(readbuffer, 2)) return false;

  SRH = readbuffer[3];
  SRH <<= 8;
  SRH |= readbuffer[4];

//  if (readbuffer[5] != crc8(readbuffer+3, 2)) return false;

 // Serial.print("ST = "); Serial.println(ST);
  double stemp = ST;
  stemp *= 175;
  stemp /= 0xffff;
  stemp = -45 + stemp;
  temp = stemp;

//  Serial.print("SRH = "); Serial.println(SRH);
  double shum = SRH;
  shum *= 100;
  shum /= 0xFFFF;

  humidity = shum;

  return true;
}

void sht31_writeCommand(uint16_t cmd)
{
  char send_data[2];
  send_data[0] = cmd >> 8;
  send_data[1] = cmd & 0xFF;
  i2c.write(SHT31_DEFAULT_ADDR<<1,send_data,2);
}


/*********************************************************************/
