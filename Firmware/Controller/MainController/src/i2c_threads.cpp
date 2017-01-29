#include "mbed.h"
#include "rtos.h"

#include "i2c_threads.h"
#include "Adafruit_SHT31.h"

I2C i2c(I2C_SDA,I2C_SCL);


float temp;
float humidity;
void sht31_writeCommand(uint16_t cmd);
void sht31_readtemphum_thread(void const *args)
{
  sht31_writeCommand(SHT31_SOFTRESET);
  Thread::wait(10);

  while(true)
  {
    char readbuffer[6];

    sht31_writeCommand(SHT31_MEAS_HIGHREP);

    Thread::wait(50);

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
  }
}

void sht31_writeCommand(uint16_t cmd)
{
  char send_data[2];
  send_data[0] = cmd >> 8;
  send_data[1] = cmd & 0xFF;
  i2c.write(SHT31_DEFAULT_ADDR<<1,send_data,2);
}

float sht31_readTemperature(void)
{
  return temp;
}

float sht31_readHumidity(void)
{
  return humidity;
}

/*********************************************************************/
