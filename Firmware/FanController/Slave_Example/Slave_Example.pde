/*************************************************************************
 * Slave_Example.pde ----- Sample sketch for making an I2C Slave Device
 * 
 * A sample sketch that shows the basic steps necessary to making
 * an I2C slave device using Arduino's Wire library.
 * 
 *
 * Copyright (c) 2011, DSS Circuits, Inc.  http://www.dsscircuits.com
 * 
 *************************************************************************/

#include <Wire.h>

/* These getX DEFINES are only used so the code will compile.  They
** simply return numbers for the function calls.  Instead you would
** use regular functions and place your GPS parsing code inside them */
#define  getLatitude()           ((unsigned long)16909060)
#define  getLongitude()          ((long)84281096)
#define  getSpeed()              ((unsigned int)2314)
#define  getSignalStatus()       ((byte)0x00)
/********************************************************************/

#define  SLAVE_ADDRESS           0x29  //slave address,any number from 0x01 to 0x7F
#define  REG_MAP_SIZE            14
#define  MAX_SENT_BYTES          3
#define  INTERRUPT_PIN           2
#define  IDENTIFICATION          0x0D

/********* Global  Variables  ***********/
byte registerMap[REG_MAP_SIZE];
byte registerMapTemp[REG_MAP_SIZE];
byte receivedCommands[MAX_SENT_BYTES];
byte newDataAvailable = 0;
byte useInterrupt = 1;
byte modeRegister = 0;
byte configRegister = 0;
byte zeroB = 0;
byte zeroC = 0;
byte zeroBData = 0;
byte zeroCData = 0;

long longitude = 0;
unsigned long latitude = 0;
unsigned int speedKPH = 0;
byte gpsStatus = 0;

void setup()
{
  if(useInterrupt)
  {
    pinMode(INTERRUPT_PIN,OUTPUT);
    digitalWrite(INTERRUPT_PIN,HIGH);
  }
  Wire.begin(SLAVE_ADDRESS); 
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  registerMap[13] = IDENTIFICATION; // ID register
}

void loop()
{
  if(zeroB || zeroC)
  {
    newDataAvailable = 0;  //let the master know we don’t have any post correction data yet
    toggleInterrupt();
    changeModeConfig();  //call the function to make your changes
    return; //go back to the beginning and start collecting data from scratch
  }
  latitude = getLatitude();                 //returns latitude as an unsigned long
  if(zeroB || zeroC)
  {
    newDataAvailable = 0;  //let the master know we don’t have any post correction data yet
    toggleInterrupt();
    changeModeConfig();  //call the function to make your changes
    return; //go back to the beginning and start collecting data from scratch
  }

  longitude = getLongitude();          //returns longitude a long
  if(zeroB || zeroC)
  {
    newDataAvailable = 0;  //let the master know we don’t have any post correction data yet
    toggleInterrupt();
    changeModeConfig();  //call the function to make your changes
    return; //go back to the beginning and start collecting data from scratch
  }

  speedKPH = getSpeed();               //returns speed as an unsigned int
  if(zeroB || zeroC)
  {
    newDataAvailable = 0;  //let the master know we don’t have any post correction data yet
    toggleInterrupt();
    changeModeConfig();  //call the function to make your changes
    return; //go back to the beginning and start collecting data from scratch
  }

  gpsStatus = getSignalStatus();     //returns status as a byte
  if(zeroB || zeroC)
  {
    newDataAvailable = 0;  //let the master know we don’t have any post correction data yet
    toggleInterrupt();
    changeModeConfig();  //call the function to make your changes
    return; //go back to the beginning and start collecting data from scratch
  }
  storeData();
  newDataAvailable = 1;
  toggleInterrupt();
}
void storeData()
{
  byte * bytePointer;  //we declare a pointer as type byte
  byte arrayIndex = 1; //we need to keep track of where we are storing data in the array
  registerMapTemp[0] = gpsStatus;  //no need to use a pointer for gpsStatus
  bytePointer = (byte*)&latitude; //latitude is 4 bytes
  for (int i = 3; i > -1; i--)
  {
    registerMapTemp[arrayIndex] = bytePointer[i];  //increment pointer to store each byte
    arrayIndex++;
  }
  bytePointer = (byte*)&longitude; //longitude is 4 bytes
  for (int i = 3; i > -1; i--)
  {
    registerMapTemp[arrayIndex] = bytePointer[i];  //increment pointer to store each byte
    arrayIndex++;
  }
  bytePointer = (byte*)&speedKPH; //speedKPH is 2 bytes
  for (int i = 1; i > -1; i--)
  {
    registerMapTemp[arrayIndex] = bytePointer[i];  //increment pointer to store each byte
    arrayIndex++;
  }
  registerMapTemp[arrayIndex] = modeRegister;
  arrayIndex++;
  registerMapTemp[arrayIndex] = configRegister;
}

void changeModeConfig()
{
  /*Put your code here to evaluate which of the registers need changing
   And how to make the changes to the given device.  For our GPS example
   It could be issuing the commands to change the baud rate, update rate,
   Datum, etc…
   We just put some basic code below to copy the data straight to the registers*/
   if(zeroB)
      {
        modeRegister = zeroBData;
        zeroB = 0;  //always make sure to reset the flags before returning from the function
        zeroBData = 0;
      }
      if(zeroC)
      {
        configRegister = zeroCData;
        zeroC = 0;  //always make sure to reset the flags before returning from the function
        zeroCData = 0;
      }
}

void toggleInterrupt()
{
  if(!useInterrupt)
  {return;} //first let’s make sure we’re using interrupts, if not just return from the function
  if(newDataAvailable)  // if new data is available set the interrupt low
  {
    digitalWrite(INTERRUPT_PIN,LOW);  //set pin low and return
    return;
  }
  //no new data available or data was just read so set interrupt pin high
  digitalWrite(INTERRUPT_PIN,HIGH); 
}

void requestEvent()
{
  if(newDataAvailable)
  {
    for (int c = 0; c < (REG_MAP_SIZE-1); c++)
    {
      registerMap[c] = registerMapTemp[c];
    }
  }
  newDataAvailable = 0;
  toggleInterrupt();
  //Set the buffer to send all 14 bytes
  Wire.send(registerMap + receivedCommands[0], REG_MAP_SIZE); 
}

void receiveEvent(int bytesReceived)
{
  for (int a = 0; a < bytesReceived; a++)
  {
    if ( a < MAX_SENT_BYTES)
    {
      receivedCommands[a] = Wire.receive();
    }
    else
    {
      Wire.receive();  // if we receive more data then allowed just throw it away
    }
  }
  if(bytesReceived == 1 && (receivedCommands[0] < REG_MAP_SIZE))
  {
    return; 
  }
  if(bytesReceived == 1 && (receivedCommands[0] >= REG_MAP_SIZE))
  {
    receivedCommands[0] = 0x00;
    return;
  }
  switch(receivedCommands[0]){
  case 0x0B:
    zeroB = 1; //this variable is a status flag to let us know we have new data in register 0x0B
    zeroBData = receivedCommands[1]; //save the data to a separate variable
    bytesReceived--;
    if(bytesReceived == 1)  //only two bytes total were sent so we’re done
    {
      return;
    }
    zeroC = 1;
    zeroCData = receivedCommands[2];
    return; //we can return here because the most bytes we can receive is three anyway
    break;
  case 0x0C:
    zeroC = 1;
    zeroCData = receivedCommands[1];
    return; //we can return here because 0x0C is the last writable register
    break;
  default:
    return; // ignore the commands and return
  }
}

