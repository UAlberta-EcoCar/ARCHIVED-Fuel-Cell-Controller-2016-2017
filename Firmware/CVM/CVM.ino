#include <Wire.h>  //Include I^2C Library (Wire Library)
#include "Linduino.h" //librays to make I2C work, still need to put them in folder 
#include "LT_I2C.h"
#include  "LTC2309.h"

//Variable for storing voltage readings
float CellVoltages[46];

void setup() {
Serial.begin(115200); 
i2c_enable();
}
 
void loop() {

  //call function collectData
  collectData();
  //process data
  //Calculate voltage of each cell relative to the one before it
  for(char CellN=45;CellN>0;CellN--)
  {
	CellVoltages[CellN] = CellVoltages[CellN] - CellVoltages[CellN-1];
  }
  //call function sendSignal
  //call function writeData
 
 }

uint8_t Channels[8] = {0x80,0xC0,0x90,0xD0,0xA0,0xE0,0xB0,0xF0};
uint8_t chipAddress[6] = {0b0001000,0b0001001,0b0001010,0b0001011,0b0011000, 0b0011001};

unsigned int adc_code;

void collectData(void) {
	char CellN = 0;
	for (uint8_t AN=0; AN< 6; AN++) {
  
		for (uint8_t ChN = 0; ChN < 8; ChN++) {
    
			//Read Channel # in Single-Ended Unipolar mode
			uint8_t adc_command = Channels[ChN] | LTC2309_UNIPOLAR_MODE;           // Set to read channel #
  
			uint8_t ack = 0;
			ack |= LTC2309_read(chipAddress[AN], adc_command, &adc_code);   // Throws out last reading
			ack |= LTC2309_read(chipAddress[AN], adc_command, &adc_code);   // Obtains the current reading and stores to adc_code variable
 
 
 
			// Convert adc_code to voltage
			uint8_t adc_voltage = LTC2309_code_to_voltage(adc_code, 2.5f, LTC2309_UNIPOLAR_MODE); //i think the interal reference voltage is 2.5
   
			if (adc_voltage < 0.1)
			{ 
				adc_voltage = CellN;  // standard voltage.. what we could expect from a channel incase one cable breaks
			}

			CellVoltages[CellN] = adc_voltage;
			CellN++;
		}
	}
}


//void sendSignal{
//if 
 // send a reply to the IP address and port that sent us the packet we received
  //  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort(Tx));//Tx??
    //Udp.write(PurgeSignal);// what does it mean to send a purge signal?
  //  Udp.endPacket();
//else 
//end; 

//}
  

//void writeData(averageVoltage) {

// Serial.println(averageVoltage);
//   delay(1000);
  
//}




