#include <Wire.h>  //Include I^2C Library (Wire Library)
#include "Linduino.h" //librays to make I2C work 
#include "LT_I2C.h"
#include  "LTC2309.h"

int sigOne = A3;
int sigTwo = A2;         

//Variable for storing voltage readings
float CellVoltages[48];



uint8_t ack = 0;
uint16_t adc_code = 0;
uint8_t adc_command =0;
float adc_voltage= 0;
float AverageAdcVoltage = 0;


int Channels[8] = {0x80,0xC0,0x90,0xD0,0xA0,0xE0,0xB0,0xF0}; //confirm int not char***
//uint16_t chipAddress[6] = {LTC2309_I2C_ADDRESS_1,LTC2309_I2C_ADDRESS_2,LTC2309_I2C_ADDRESS_3,LTC2309_I2C_ADDRESS_4,LTC2309_I2C_ADDRESS_5,LTC2309_I2C_ADDRESS_6}; 
uint16_t chipAddress[6] = {0x08,0x09,0x0A,0x0B,0x18,0x19}; 
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

//if(CellVoltages[] < 0.1 ) 
//         {
//          digitalWrite(sigTwo, HIGH);   // signals that a cvm probe is disconnected 
//             }
//
//
//if ((CellVoltages > 0.1) && (CellVoltages < 0.5)) //purge signal
//    {
//           digitalWrite(sigOne, HIGH);  // sends signal to FCC 
//           delay (2000);   
//           digitalWrite(sigOne, LOW);// turn off signal 
//           delay (2000);   
//           }
//           //signals working!!
//


writeData();  //call function writeData

}
                  

void collectData(void) {

    for (int chip=0; chip< 6; chip++) 
  {
  int CellN = 0;
 
  for (int Channel_number = 0; Channel_number < 8; Channel_number++) 
    {
          
        for (int N = 0; N<20; N ++)
        {
          
            AverageAdcVoltage = 0;
    
            //Read Channel # in Single-Ended Unipolar mode
            adc_command = Channels[Channel_number] | LTC2309_UNIPOLAR_MODE;        // Set to read channel #
       
           ack |= LTC2309_read(chipAddress[chip], adc_command, &adc_code);   // Throws out last reading
           ack |= LTC2309_read(chipAddress[chip], adc_command, &adc_code);   // Obtains the current reading and stores to adc_code variable
    
 
            // Convert adc_code to voltage
            adc_voltage = LTC2309_code_to_voltage(adc_code, 2.5f, LTC2309_UNIPOLAR_MODE); //accuracy changes as you change internal ref... maybe try and change it if readings are off
            adc_voltage = (adc_voltage);
           
            

            //calculating the average of the 20 voltages read on a channel
            AverageAdcVoltage = (AverageAdcVoltage + adc_voltage);
          
           
          }
          
           CellVoltages[CellN] = (AverageAdcVoltage)/20;
          CellN =(CellN + 1);
         
          
    }
  }
     
}


void writeData(void) { 

 
  for(int count = 0; count < 46; count++ )  { 
    
         for (int Read = 0;  Read< 6; Read++ )   
          {
             Serial.print( "Chip Number" );
              Serial.print( Read );
              Serial.print( ':' ); 
              delay (600);
              
                    for (int values= 0; values < 8; values++)
                       {
                         Serial.print( "Chan # " );
                         Serial.print( values );
                         Serial.print( " : " );
                         delay (600);
                         Serial.print( CellVoltages[count] ); 
                         Serial.print( ',' ); 
                         delay (600);
                        }
   
    }
  }
}



  




