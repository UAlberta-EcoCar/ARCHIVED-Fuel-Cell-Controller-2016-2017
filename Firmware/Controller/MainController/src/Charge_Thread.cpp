#include "mbed.h"
#include "rtos.h"
#include "FC_Status.h"
#include "Pin_Defines.h"
#include "analog_read_thread.h"
#include "Charge_Thread.h"

DigitalOut fcc_charge_relay(CHARGE_R);
DigitalOut fcc_cap_relay(CAP_R);
DigitalOut fcc_powerboard_relay(FCC_R);

void charge_thread(void const *args)
{
  while(get_fc_status()!=CHARGE_STATE)
  {
    Thread::wait(500);
  }

  //close cap charge relay
  fcc_charge_relay = 1;

  while(get_capvolt()<CHARGE_THRES_L)
  {
    Thread::wait(50);
  }

  fcc_charge_relay = 0;
  Thread::wait(500);

  //close cap relay
  fcc_cap_relay = 1;

  while(get_capvolt()<CHARGE_THRES_H)
  {
    Thread::wait(50);
  }

  set_fc_status(RUN_STATE);
}
