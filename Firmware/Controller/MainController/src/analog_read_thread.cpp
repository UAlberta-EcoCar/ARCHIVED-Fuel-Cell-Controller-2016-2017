#include "mbed.h"
#include "rtos.h"

#include "analog_read_thread.h"
#include "Pin_Defines.h"

Timer t;

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

double fc_coulumbs_v;
double fc_joules_v;
double cap_coulumbs_v;
double cap_joules_v;

float get_capvolt(void){return(capvolt_v);}
float get_fccurr(void){return(fccurr_v);}
float get_fcvolt(void){return(fcvolt_v);}
float get_capcurr(void){return(capcurr_v);}
float get_fcpres(void){return(fcpres_v);}

double get_fc_coulumbs(void){return(fc_coulumbs_v);}
double get_fc_joules(void){return(fc_joules_v);}
double get_cap_coulumbs(void){return(cap_coulumbs_v);}
double get_cap_joules(void){return(cap_joules_v);}

void analog_read_thread(void const *args)
{
  t.start();
  Thread::wait(5);
  while(true)
  {
    capvolt_v = capvolt;
    fccurr_v = fccurr;
    fcvolt_v = fcvolt;
    capcurr_v = capcurr;
    fcpres_v = fcpres;

    float dt = t.read();
    t.reset();

    //integration of data
    fc_coulumbs_v += fccurr_v*dt;
    fc_joules_v += fccurr_v*fcvolt_v*dt;
    cap_coulumbs_v += capcurr_v*dt;
    cap_joules_v += capcurr_v*capvolt_v*dt;

    Thread::wait(5);
  }
}
