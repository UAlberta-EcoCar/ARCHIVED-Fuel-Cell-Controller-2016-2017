#include "mbed.h"
#include "rtos.h"

#include "Pin_Defines.h"
#include "multiplexor.h"
#include "analog_read_thread.h"
#include "data_logging_thread.h"
#include "error_checking_thread.h"

DigitalOut status_led(STATUS_LED);

int main()
{
  Thread analog_read_t(analog_read_thread);
  Thread error_checking_t(error_checking_thread);
  Thread data_logging_t(data_logging_thread);

  while(true)
  {
    status_led = !status_led;
    Thread::wait(500);
  }
}
