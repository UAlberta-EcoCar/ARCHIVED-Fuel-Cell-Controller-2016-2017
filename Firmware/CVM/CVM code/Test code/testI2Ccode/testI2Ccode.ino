#include <Wire.h>  //Include I^2C Library (Wire Library)
#include "Linduino.h" //librays to make I2C work 
#include "LT_I2C.h"
#include  "LTC2309.h"

int sigOne = A3;
int sigTwo = A2;         

//Variable for storing voltage readings
float CellVoltages = LTC2309_CH0;
// increment variable
int CellN = 0;

uint8_t ack = 0;
uint16_t adc_code = 0;
uint8_t adc_command =0;
float adc_voltage= 0;


//int Channels[8] = {0x80,0xC0,0x90,0xD0,0xA0,0xE0,0xB0,0xF0}; //confirm int not char***
//uint16_t chipAddress[6] = {LTC2309_I2C_ADDRESS_1,LTC2309_I2C_ADDRESS_2,LTC2309_I2C_ADDRESS_3,LTC2309_I2C_ADDRESS_4,LTC2309_I2C_ADDRESS_5,LTC2309_I2C_ADDRESS_6}; 

void setup() {
Serial.begin(9600); 

Wire.begin(); 
pinMode(sigOne, OUTPUT);  // sets the digital pin as output
pinMode(sigTwo, OUTPUT); // sets the digital pin as output

digitalWrite(sigOne, LOW);
 digitalWrite(sigTwo, LOW);
}
 
void loop() 
{
 collectData(); //call function collectData

if(CellVoltages < 0.1 ) 
         {
          digitalWrite(sigTwo, HIGH);   // signals that a cvm probe is disconnected 
             }


if ((CellVoltages > 0.1) && (CellVoltages < 0.5)) //purge signal
    {
           digitalWrite(sigOne, HIGH);  // sends signal to FCC 
           delay (2000);   
           digitalWrite(sigOne, LOW);// turn off signal 
           delay (2000);   
           }
           //signals working!!



writeData();  //call function writeData

}
                  
                  



void collectData(void) {

    adc_command = LTC2309_CH0 | LTC2309_UNIPOLAR_MODE;                  // Build ADC command for channel 0

    ack |= LTC2309_read(LTC2309_I2C_ADDRESS_1, adc_command, &adc_code);   // Throws out last reading
    delay(50);
    ack |= LTC2309_read(LTC2309_I2C_ADDRESS_1, adc_command, &adc_code);   // Obtains the current reading and stores to adc_code variable

    // Convert adc_code to voltage
    adc_voltage = LTC2309_code_to_voltage(adc_code,  4.5f , LTC2309_UNIPOLAR_MODE ); //i think the interal reference voltage is 2.5    
    CellVoltages = adc_voltage;   


}


void writeData(void) { //works!!!!
  Serial.print( CellVoltages );
  delay (500);
  Serial.print( "," );// add comma, all one line no space
  delay(500);
}




  




