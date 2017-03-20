#include <Wire.h>  //Include I^2C Library (Wire Library)
#include "Linduino.h" //librays to make I2C work 
#include "LT_I2C.h"
#include  "LTC2309.h"


 
int sigOne = A3;                // sig 1 connected to FCC ethernet pin 5, is this right?
int sigTwo = A2;                // sig 1 connected to FCC ethernet pin 6, is this right?

//Variable for storing voltage readings
float CellVoltages[46];
// increment variable
int CellN = 0;
// holds average voltage value
int AverageAdcVoltage=0;
// i2c variables
 uint8_t ack = 0;
 uint16_t adc_code = 0;

int Channels[8] = {0x80,0xC0,0x90,0xD0,0xA0,0xE0,0xB0,0xF0}; //confirm int not char***
int chipAddress[6] = {0b0001000,0b0001001,0b0001010,0b0001011,0b0011000, 0b0011001};
int arrayAdcVoltage[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


void setup() {
Serial.begin(9600); 
Wire.begin(); 
pinMode(sigOne, OUTPUT);              // sets the digital pin as output
pinMode(sigTwo, OUTPUT); // sets the digital pin as output
digitalWrite(sigOne, LOW);  // turn off signal
digitalWrite(sigTwo, LOW);  // turn off signal
}
char p = 0;

void loop() 
{
 
   
collectData(); //call function collectData

  //Calculate voltage of each cell relative to the one before it
  for(char CellN=45;CellN>0;CellN--)
   {
   CellVoltages[CellN] = CellVoltages[CellN] - CellVoltages[CellN-1];
       //send signal to show that pin is disconnected 
               if (CellVoltages[CellN] <0.1)
                {
                    digitalWrite(sigTwo, HIGH);   // sets singal that a pin is disconnected on
                 
    
                     }
                if ((0.1< CellVoltages[CellN]) && (CellVoltages[CellN] <0.5)) //purge signal
                  {
                     digitalWrite(sigOne, HIGH);   // sends signal to FCC 
                     delay(1500); // waits half a second
                     digitalWrite(sigOne, LOW);   // sends signal to FCC 
                     delay(1500);

                   }
   }
                   
 writeData();  //call function writeData

}  



void collectData(void) {
  for (int chip=0; chip< 6; chip++) {
  

    for (int Channel_number = 0; Channel_number < 8; Channel_number++) {
    
        for (int N = 0; N<20; N ++){
    
        //Read Channel # in Single-Ended Unipolar mode
        uint8_t adc_command = Channels[ Channel_number] | LTC2309_UNIPOLAR_MODE;           // Set to read channel #
  
        ack = 0;
        adc_code = 0;
        ack |= LTC2309_read(chipAddress[chip], adc_command, &adc_code);   // Throws out last reading
        ack |= LTC2309_read(chipAddress[chip], adc_command, &adc_code);   // Obtains the current reading and stores to adc_code variable
    
 
        // Convert adc_code to voltage
        uint8_t adc_voltage = LTC2309_code_to_voltage(adc_code, 2.5f, LTC2309_UNIPOLAR_MODE); //i think the interal reference voltage is 2.5


        //calculating the average of the 20 voltages read on a channel
      
               while((millis()%100)!= 0); //delay 
               
               AverageAdcVoltage = (AverageAdcVoltage + adc_voltage);
               
              }

              
               CellVoltages[CellN] = (AverageAdcVoltage)/20;
               CellN =(CellN + 1);
        }
       
    
      }
}


void writeData(void) {
  
for (int out = 0; out<46; out ++){
  Serial.print( CellVoltages[out] );
  Serial.print( "," );// add comma, all one line no space?
  delay(1000);
  } 
}

  




