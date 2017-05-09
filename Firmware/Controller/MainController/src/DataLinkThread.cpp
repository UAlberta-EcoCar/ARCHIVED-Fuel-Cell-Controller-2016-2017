#include "mbed.h"
#include "rtos.h"

#include "Pin_Defines.h"
#include "DataLinkThread.h"
#include "analog_read_thread.h"
#include "i2c_threads.h"
#include "FC_Status.h"
#include "error_checking_thread.h"
#include "Run_Thread.h"

//This thread communicates with a other systems over CAN Bus or BlueTooth

Serial link_serial(LINK_TX,LINK_RX,115200);



void data_link_thread(void const *args)
{
  while(true)
  {
    link_serial.printf("{\"speed\":");
    link_serial.printf("%f",get_fctemp());
    link_serial.printf(",\"fc_voltage\":");
    link_serial.printf("%f",get_fcvolt());
    link_serial.printf(",\"motor_current\":");
    link_serial.printf("%f",get_fccurr());
    link_serial.printf(",\"fc_alarm_code\":");
    link_serial.printf("%d",get_error_state());
    link_serial.printf(",\"fc_state\":");
    link_serial.printf("%d",get_fc_status());
    link_serial.printf(",\"fc_temp\":");
    link_serial.printf("%d",(int)get_fctemp());
    link_serial.printf(",\"efficiency\":");
    link_serial.printf("%d",get_purge_count());
    link_serial.printf("}\n");

    Thread::wait(2000);
  }
}
