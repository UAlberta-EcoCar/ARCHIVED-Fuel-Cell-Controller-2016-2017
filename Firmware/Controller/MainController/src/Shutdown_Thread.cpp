#include "mbed.h"
#include "rtos.h"

#include "Shutdown_Thread.h"
#include "digital_io.h"
#include "FC_Status.h"

Timer shutdown_timer;

void shutdown_thread(void const *args)
{
  while(get_fc_status()!=STOP_STATE)
  {
    Thread::wait(10);
  }

  //start shutdown timer (allows for few seconds of data logging before powering down controller)
  shutdown_timer.start();

  while(1)
  {
    supply_valve(0);
    purge_valve(0);
    start_relay(0);
    motor_relay(0);
    charge_relay(0);
    cap_relay(0);
    Thread::wait(10);
    if(shutdown_timer.read()>3)
    {
      fcc_relay(0);
    }
  }
}
