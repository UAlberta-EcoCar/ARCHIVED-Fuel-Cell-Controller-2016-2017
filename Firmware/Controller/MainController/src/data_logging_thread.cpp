#include "mbed.h"
#include "rtos.h"

#include "Pin_Defines.h"
#include "data_logging_thread.h"
#include "analog_read_thread.h"
#include "i2c_threads.h"

Serial ol_serial(OL_TX,OL_RX,115200);

void data_logging_thread(void const *args)
{
  while(true)
  {
    ol_serial.printf("yo this is a test\r\n");
    ol_serial.printf("data is being logged to an sd card\r\n");
    ol_serial.printf("The temp is %f\r\n",sht31_readTemperature());
    ol_serial.printf("The humidity is %f\r\n",sht31_readHumidity());
    Thread::wait(50);
  }
}
