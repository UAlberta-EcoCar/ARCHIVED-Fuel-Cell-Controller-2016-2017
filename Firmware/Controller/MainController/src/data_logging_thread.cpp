#include "mbed.h"
#include "rtos.h"

#include "Pin_Defines.h"
#include "data_logging_thread.h"
#include "analog_read_thread.h"
#include "i2c_threads.h"
#include "FC_Status.h"

Serial ol_serial(OL_TX,OL_RX,115200);

Timer deltatimer; //will overflow ever 30 minutes

void data_logging_thread(void const *args)
{
  Thread::wait(500);
  deltatimer.start();
  ol_serial.printf("time,");
  ol_serial.printf("deltat,");
  ol_serial.printf("fc_status,");
  ol_serial.printf("ExternalTemp,");
  ol_serial.printf("ExternalHumidity,");
  ol_serial.printf("CapVolt,");
  ol_serial.printf("FCVolt,");
  ol_serial.printf("CapCurr,");
  ol_serial.printf("FCCurr,");
  ol_serial.printf("FCPres,");
  ol_serial.printf("FCCoulumbs,");
  ol_serial.printf("FCJoules,");
  ol_serial.printf("CapCoulumbs,");
  ol_serial.printf("CapJoules,");
  ol_serial.printf("\r\n");
  while(true)
  {
    ol_serial.printf("%s,",get_time());
    deltatimer.stop();
    ol_serial.printf("%s,",deltatimer.read_ms());
    deltatimer.reset();
    deltatimer.start();
    ol_serial.printf("%d,",get_fc_status());
    ol_serial.printf("%f,",sht31_readTemperature());
    ol_serial.printf("%f,",sht31_readHumidity());
    ol_serial.printf("%f,",get_capvolt());
    ol_serial.printf("%f,",get_fcvolt());
    ol_serial.printf("%f,",get_capcurr());
    ol_serial.printf("%f,",get_fccurr());
    ol_serial.printf("%f,",get_fcpres());
    ol_serial.printf("%f,",get_fc_coulumbs());
    ol_serial.printf("%f,",get_fc_joules());
    ol_serial.printf("%f,",get_cap_coulumbs());
    ol_serial.printf("%f,",get_cap_joules());
    ol_serial.printf("\r\n");
    Thread::wait(200);
  }
}
