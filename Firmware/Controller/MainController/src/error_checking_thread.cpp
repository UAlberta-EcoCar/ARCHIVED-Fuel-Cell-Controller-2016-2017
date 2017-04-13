#include "mbed.h"
#include "rtos.h"

#include "error_checking_thread.h"
#include "analog_read_thread.h"
#include "i2c_threads.h"
#include "FC_Status.h"
#include "multiplexor.h"

#define OVER_VOLT 10
#define UNDER_VOLT 11
#define OVER_PRES 6
#define UNDER_PRES 7
#define OVER_CURR 8
#define OVER_TEMP 5
#define H2_ALARM 3

char error_state;

Timer low_pres_timer;
Timer high_temp_timer;

void error_checking_thread(void const *args)
{
  error_state = 0;
  
  while(get_fc_status()==IDLE_STATE)
  {
    Thread::wait(10);
  }

  low_pres_timer.start();
  high_temp_timer.start();

  while(get_fc_status()!=IDLE_STATE)
  {
    if(get_fcvolt()>(1.1*28))
    {
      error_state|=(1<<OVER_VOLT);
    }
    if(get_capvolt()>(16*2))
    {
      error_state|=(1<<OVER_VOLT);
    }

    if(get_fcpres()>8)
    {
      error_state|=(1<<OVER_PRES);
    }

    //low pressure is on a timer
    if(get_fcpres()>4)
    {
      //reset Timer
      low_pres_timer.reset();
    }
    else
    {
      if(low_pres_timer.read()>5)
      {
        error_state|=(1<<UNDER_PRES);
      }
    }

    //high temp is also on a timer
    if(get_fctemp()<60)
    {
      //reset timer
      high_temp_timer.reset();
    }
    else
    {
      if(high_temp_timer.read()>5)
      {
        error_state|=(1<<OVER_TEMP);
      }
    }

    if(~read_H2_OK())
    {
      error_state|=(1<<H2_ALARM);
    }

    if(error_state)
    {
      set_fc_status(STOP_STATE);
    }

    Thread::wait(5);
  }
}

char get_error_state(void)
{
  return(error_state);
}
