#include "Linduino.h"
#include "LT_I2C.h"
#include  "LTC2309.h"

void setup ()
{
  Serial.begin(9600);
  i2c_enable();
}

uint16_t adc_code; //"LTC2309_read()" function stores the result in this variable

void loop ()
{
  //Read Channel 0 in Single-Ended Unipolar mode

  uint8_t adc_command = LTC2309_CH0 | LTC2309_UNIPOLAR_MODE;                  // Set to read channel 0
  
  uint8_t ack = 0;
  ack |= LTC2309_read(LTC2309_I2C_ADDRESS, adc_command, &adc_code);   // Throws out last reading
  ack |= LTC2309_read(LTC2309_I2C_ADDRESS, adc_command, &adc_code);   // Obtains the current reading and stores to adc_code variable

  // Convert adc_code to voltage
  uint8_t adc_voltage = LTC2309_code_to_voltage(adc_code, 2.5f, LTC2309_UNIPOLAR_MODE); //i think the interal reference voltage is 2.5

  Serial.println(adc_voltage);
  
  delay(1000);
}

