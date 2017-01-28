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
#include <USBSerial.h>


#include "Pin_Defines.h"
#include "analog_read_thread.h"
#include "error_checking_thread.h"
#include "data_logging_thread.h"
#include "startup_thread.h"

DigitalOut supply_valve(SUPPLY_V);
DigitalOut purge_valve(PURGE_V);
DigitalOut fcc_resist_relay(FCC_R);

// Values to reach on start up (pretty much made up at this point)
#define FC_PRES1 30
#define FC_PRES2 60
#define FC_VOLT 30

void startup_thread(void const *args){

  // Sleep threads that would interfere with startup

  // Begin startup
  supply_valve = 1;

  // Wait for pressure and voltage to reach the required level
  while((get_fcpres() <= FC_PRES1) && (get_fcvolt() <= FC_VOLT)){
    Thread::wait(1);
  }

  fcc_resist_relay = 1;
  purge_valve = 1;

  Thread::wait(1000);

  fcc_resist_relay = 0;
  purge_valve = 0;

  while((get_fcpres() <= FC_PRES2)){
    Thread::wait(1);
  }
}
