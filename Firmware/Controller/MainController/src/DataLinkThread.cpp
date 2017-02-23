#include "mbed.h"
#include "rtos.h"

#include "Pin_Defines.h"
#include "DataLinkThread.h"
#include "analog_read_thread.h"

//This thread communicates with a other systems over CAN Bus or BlueTooth

Serial link_serial(LINK_TX,LINK_RX,115200);

//Functions for formatting as json
void json_start(void)
{
  link_serial.printf("{");
}

void json_data(char * name,float value,char last)
{
  if(last)
  {
    link_serial.printf("\"%s\":%f",name,value); //no comma on line
  }
  else
  {
    link_serial.printf("\"%s\":%f,",name,value); //comma on line
  }
}

void json_end(void)
{
  link_serial.printf("}\n");
}


char count;

void data_link_thread(void const *args)
{
  while(true)
  {
    json_start();
    json_data("count",count,1);
    json_end();

    count++;
    Thread::wait(500);
  }
}
