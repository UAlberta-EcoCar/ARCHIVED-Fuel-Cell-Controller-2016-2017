#include <mbed.h>
#include <rtos.h>
#include <USBSerial.h>

#include "Pin_Defines.h"
#include "analog_read_thread.h"
#include "error_checking_thread.h"
#include "data_logging_thread.h"
#include "i2c_threads.h"
#include "DataLinkThread.h"
#include "FC_Status.h"
#include "startup_thread.h"
#include "Charge_Thread.h"
#include "Run_Thread.h"
#include "Shutdown_Thread.h"
#include "multiplexor.h"
#include "digital_io.h"

DigitalOut status_led(STATUS_LED);

int main() {
  fcc_relay(0);
  motor_relay(0);
  cap_relay(0);
  start_relay(0);
  charge_relay(0);
  supply_valve(0);
  purge_valve(0);

  Thread::wait(2000);

  set_fc_status(IDLE_STATE);

  Thread analog_read_t(analog_read_thread,NULL,osPriorityNormal,256*4);
  Thread::wait(1000);

  Thread error_checking_t(error_checking_thread,NULL,osPriorityNormal,256*4);
  Thread::wait(1000);

  Thread data_logging_t(data_logging_thread,NULL,osPriorityNormal,256*4);
  Thread sht31_readtemphum_t(sht31_readtemphum_thread,NULL,osPriorityNormal,256*4);
  Thread set_indicator_leds_t(set_indicator_leds_thread,NULL,osPriorityNormal,256*4);
  Thread fan_control_board_t(fan_control_board_thread,NULL,osPriorityNormal,256*4);

  Thread data_link_t(data_link_thread,NULL,osPriorityNormal,256*4);
  Thread ds3231_t(ds3231_thread,NULL,osPriorityNormal,256*4);
  Thread motor_command_t(motor_command_thread,NULL,osPriorityNormal,256*4);

  Thread startup_t(startup_thread,NULL,osPriorityNormal,256*4);
  Thread charge_t(charge_thread,NULL,osPriorityNormal,256*4);
  Thread run_t(run_thread,NULL,osPriorityNormal,256*4);
  Thread shutdown_t(shutdown_thread,NULL,osPriorityNormal,256*4);
  fcc_relay(1);

  Thread::wait(1000);
  set_fc_status(START_STATE);

  uint8_t count = 0;

  while (true)
  {
    status_led = !status_led;
    set_fan_pwr_status(1);

    Thread::wait(500);
  }
}
