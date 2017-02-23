#include "mbed.h"
#include "rtos.h"

#include "analog_read_thread.h"
#include "Pin_Defines.h"

AnalogIn capvolt(CAPVOLT);
AnalogIn fccurr(FCCURR);
AnalogIn fcvolt(FCVOLT);
AnalogIn capcurr(CAPCURR);
AnalogIn fcpres(FCPRES);

float capvolt_v;
float fccurr_v;
float fcvolt_v;
float capcurr_v;
float fcpres_v;

float get_capvolt(void){return(capvolt_v);}
float get_fccurr(void){return(fccurr_v);}
float get_fcvolt(void){return(fcvolt_v);}
float get_capcurr(void){return(capcurr_v);}
float get_fcpres(void){return(fcpres_v);}

void analog_read_thread(void const *args)
{
  while(true)
  {
    capvolt_v = capvolt;
    fccurr_v = fccurr;
    fcvolt_v = fcvolt;
    capcurr_v = capcurr;
    fcpres_v = fcpres;
    
    Thread::wait(5);
  }
}
