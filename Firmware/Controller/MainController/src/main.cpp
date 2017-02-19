#include <mbed.h>
#include <rtos.h>
#include <USBSerial.h>

#include "Pin_Defines.h"
#include "analog_read_thread.h"
#include "error_checking_thread.h"
#include "data_logging_thread.h"
#include "i2c_threads.h"
#include "DataLinkThread.h"

USBSerial serial;

DigitalOut status_led(STATUS_LED);

int main() {
    Thread::wait(1000);

    Thread analog_read_t(analog_read_thread,NULL,osPriorityNormal,256*4);
    Thread error_checking_t(error_checking_thread,NULL,osPriorityNormal,256*4);
    Thread data_logging_t(data_logging_thread,NULL,osPriorityNormal,256*4);
    Thread sht31_readtemphum_t(sht31_readtemphum_thread,NULL,osPriorityNormal,256*4);
    Thread set_indicator_leds_t(set_indicator_leds_thread,NULL,osPriorityNormal,256*4);
    Thread fan_control_board_t(fan_control_board_thread,NULL,osPriorityNormal,256*4);
    Thread data_link_t(data_link_thread,NULL,osPriorityNormal,256*4);

    while (true)
    {
        status_led = !status_led;
        serial.printf("Hello World!\r\n");

        Thread::wait(500);
    }
}
