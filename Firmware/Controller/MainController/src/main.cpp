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

USBSerial serial;
DigitalOut status_led(STATUS_LED);

char * datetime; //pointer to array for storing date/time

int main() {
    Thread::wait(1000);

    Thread analog_read_t(analog_read_thread,NULL,osPriorityNormal,256*4);
//    Thread error_checking_t(error_checking_thread,NULL,osPriorityNormal,256*4);
    Thread data_logging_t(data_logging_thread,NULL,osPriorityNormal,256*4);
    Thread sht31_readtemphum_t(sht31_readtemphum_thread,NULL,osPriorityNormal,256*4);
    Thread set_indicator_leds_t(set_indicator_leds_thread,NULL,osPriorityNormal,256*4);
    Thread fan_control_board_t(fan_control_board_thread,NULL,osPriorityNormal,256*4);
    Thread data_link_t(data_link_thread,NULL,osPriorityNormal,256*4);
    Thread ds3231_t(ds3231_thread,NULL,osPriorityNormal,256*4);

//    Thread startup_t(startup_thread,NULL,osPriorityNormal,256*4);
//    Thread charge_t(charge_thread,NULL,osPriorityNormal,256*4);
//    Thread run_t(run_thread,NULL,osPriorityNormal,256*4);
//    Thread shutdown_t(shutdown_thread,NULL,osPriorityNormal,256*4);

    set_fc_status(START_STATE);

    uint8_t count = 0;

    while (true)
    {
        status_led = !status_led;

        set_indicator_leds(1<<count);
        count++;
        if(count>11)
        {
          count=0;
        }

        serial.printf("Hello World!\r\n");

        serial.printf("The time is: %s",get_time());

        serial.printf("\r\n");
        serial.printf("The Temp Outside is: %f\r\n",sht31_readTemperature());
        serial.printf("The Humidity Outside is: %f\r\n",sht31_readHumidity());
        serial.printf("Fuel Cell Status is: %d\r\n",get_fc_status());

        serial.printf("H2 Status%d\r\n",read_H2_OK());

        Thread::wait(500);
    }
}
