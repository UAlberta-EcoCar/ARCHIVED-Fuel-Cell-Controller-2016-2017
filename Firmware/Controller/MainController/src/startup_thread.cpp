/*
  Open Supply Valve
  Wait for hydrogen pressure to reach certain level and voltage to reach certain level
  Open purge Valve
  Close start up resistor relay
  1 seocnd
  Open start up ressitor relay
  Close p v
  Wait for pressure toreach certain level
*/
#include <mbed.h>
#include <rtos.h>

#include "Pin_Defines.h"
#include "analog_read_thread.h"
#include "error_checking_thread.h"
#include "data_logging_thread.h"
#include "startup_thread.h"
#include "FC_Status.h"
#include "digital_io.h"
#include "i2c_threads.h"

// Values to reach on start up (pretty much made up at this point)
#define FC_PRES1 5.0f
#define FC_PRES2 4.0f
#define FC_VOLT 20.0f

void startup_thread(void const *args){

  // wait for start signal
  while(get_fc_status()!=START_STATE)
  {
    Thread::wait(50);
  }
  set_indicator_leds(1<<0);
  // Open Supply Valve to let Hydrogen in
  supply_valve(1);


  // Wait for pressure and voltage to reach the required level
  while((get_fcpres() < FC_PRES1))
  {
    Thread::wait(10);
  }
  while(get_fcvolt() < FC_VOLT)
  {
    Thread::wait(10);
  }

  // Close resistor relay to allow current draw
  start_relay(1);
  // open purge vale
  purge_valve(1);

  //wait for 1 second
  Thread::wait(1000);

  //open relay, close valve
  start_relay(0);
  purge_valve(0);

  Thread::wait(500); //delay for relay to fully close

  //wait for pressure to recover
  while((get_fcpres() < FC_PRES2))
  {
    Thread::wait(10);
  }

  set_fc_status(CHARGE_STATE);

  while(1)
  {
    Thread::wait(2000);
  }
}
