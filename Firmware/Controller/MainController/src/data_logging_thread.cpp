#include "mbed.h"
#include "rtos.h"

#include "Pin_Defines.h"
#include "data_logging_thread.h"
#include "analog_read_thread.h"

Serial ol_serial(OL_TX,OL_RX,9600);

void data_logging_thread(void const *args)
{
  ol_serial.printf("yo this is a test\n");
  
  Thread::wait(200);
}
