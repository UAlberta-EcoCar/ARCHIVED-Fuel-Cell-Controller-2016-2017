#include "mbed.h"
#include "digital_io.h"
#include "Pin_Defines.h"

//functions for accessing digital io functions from other locations

DigitalOut supply_v(SUPPLY_V);
DigitalOut purge_v(PURGE_V);
DigitalOut start_r(START_R);
DigitalOut motor_r(MOTOR_R);
DigitalOut charge_r(CHARGE_R);
DigitalOut cap_r(CAP_R);
DigitalOut fcc_r(FCC_R);

void supply_valve(bool val)
{
  supply_v = val;
}

void purge_valve(bool val)
{
  purge_v = val;
}

void start_relay(bool val)
{
  start_r = val;
}

void motor_relay(bool val)
{
  motor_r = val;
}

void charge_relay(bool val)
{
  charge_r = val;
}

void cap_relay(bool val)
{
  cap_r = val;
}

void fcc_relay(bool val)
{
  fcc_r = val;
}
