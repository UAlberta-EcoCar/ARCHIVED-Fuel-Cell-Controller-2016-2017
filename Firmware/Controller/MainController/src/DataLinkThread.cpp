#include "mbed.h"
#include "rtos.h"

#include "Pin_Defines.h"
#include "DataLinkThread.h"
#include "analog_read_thread.h"
#include "i2c_threads.h"
#include "FC_Status.h"

//This thread communicates with a other systems over CAN Bus or BlueTooth

Serial link_serial(LINK_TX,LINK_RX,115200);

//Functions for formatting as json
void json_start(void)
{
  link_serial.printf("{");
}

void json_datafloat(char * name,float value,char last)
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

void json_dataint(char * name,int value,char last)
{
  if(last)
  {
    link_serial.printf("\"%s\":%d",name,value); //no comma on line
  }
  else
  {
    link_serial.printf("\"%s\":%d,",name,value); //comma on line
  }
}

void json_datastring(char * name,char * value,char last)
{
  if(last)
  {
    link_serial.printf("\"%s\":\"%s\"",name,value); //no comma on line
  }
  else
  {
    link_serial.printf("\"%s\":\"%s\",",name,value); //comma on line
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

    json_datastring("time",get_time(),0);
    json_dataint("status",get_fc_status(),0);
    json_datafloat("ExternalTemp",sht31_readTemperature(),0);
    json_datafloat("ExternalHumidity",sht31_readHumidity(),0);
    json_datafloat("CapVolt",get_capvolt(),0);
    json_datafloat("FCVolt",get_fcvolt(),0);
    json_datafloat("CapCurr",get_capcurr(),0);
    json_datafloat("FCCurr",get_fccurr(),0);
    json_datafloat("FCPres",get_fcpres(),0);
    json_datafloat("FCCoulumbs",get_fc_coulumbs(),0);
    json_datafloat("FCJoules",get_fc_joules(),0);
    json_datafloat("CapCoulumbs",get_cap_coulumbs(),0);
    json_datafloat("CapJoules",get_cap_joules(),1);

    json_end();

    Thread::wait(500);
  }
}
