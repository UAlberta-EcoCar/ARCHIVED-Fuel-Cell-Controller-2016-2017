#include "mbed.h"
#include "rtos.h"

#include "Run_Thread.h"
#include "Pin_Defines.h"
#include "analog_read_thread.h"
#include "FC_Status.h"
#include "multiplexor.h"
#include "i2c_threads.h"
#include "digital_io.h"

float purge_count;
float coulumb_count_at_last_purge;

void run_thread(void const *args)
{
  coulumb_count_at_last_purge = get_fc_coulumbs();

  while(get_fc_status()!=RUN_STATE)
  {
    Thread::wait(200);
  }

  while(1)
  {
    if(get_fc_status()==STOP_STATE)
    {
      Thread::wait(1000);
    }

    if(get_fc_coulumbs()-coulumb_count_at_last_purge>2300)
    {
      purge_valve(1);
      Thread::wait(200);
      purge_valve(0);
      purge_count++;
      coulumb_count_at_last_purge = get_fc_coulumbs();
    }

    if(read_M_SIG_1()|read_M_SIG_2())
    {
      set_fan_pwr_status(0b111); //turn fans on
      while(~get_fan_status()) //wait for fans to turn on
      {
        Thread::wait(200);
      }
      Thread::wait(500);
      //give power to the motor_relay
      motor_relay(1);
    }
    else if(get_fcvolt()>VOLTAGE_THRESHOLD)
    {
      motor_relay(0); //turn motor off
      set_fan_pwr_status(0);
    }
    else
    {
      set_fan_pwr_status(0b111);
    }

    Thread::wait(20);
  }
}
