#include "mbed.h"
#include "digital_io.h"
#include "Pin_Defines.h"
#include "analog_read_thread.h"

//functions for accessing digital io functions from other locations

DigitalOut supply_v(SUPPLY_V);
DigitalOut purge_v(PURGE_V);
DigitalOut start_r(START_R);
DigitalOut motor_r(MOTOR_R);
DigitalOut charge_r(CHARGE_R);
DigitalOut cap_r(CAP_R);
DigitalOut fcc_r(FCC_R);

bool get_supply_valve()
{
  return(supply_v);
}

void supply_valve(bool val)
{
  supply_v = val;
}

bool get_purge_valve()
{
  return(purge_v);
}

void purge_valve(bool val)
{
  purge_v = val;
}

bool get_start_relay()
{
  return(start_r);
}

void start_relay(bool val)
{
  if(charge_r == 0)
  {
    if(cap_r == 0)
    {
      start_r = val;
    }
  }
}

bool get_motor_relay()
{
  return(motor_r);
}

void motor_relay(bool val)
{
  motor_r = val;
}

bool get_charge_relay()
{
  return(charge_r);
}

void charge_relay(bool val)
{
  if(start_r == 0)
  {
    if(cap_r == 0)
    {
      charge_r = val;
    }
  }
}

bool get_cap_relay()
{
  return(cap_r);
}

void cap_relay(bool val)
{
  if(start_r == 0)
  {
    if(charge_r == 0)
    {
      if(get_capvolt()>19.0f)
      {
        cap_r = val;
      }
    }
  }
}

bool get_fcc_relay()
{
  return(fcc_relay);
}

void fcc_relay(bool val)
{
  fcc_r = val;
}
