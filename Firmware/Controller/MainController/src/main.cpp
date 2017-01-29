#include <mbed.h>
#include <rtos.h>
#include <USBSerial.h>

#include "Pin_Defines.h"
#include "analog_read_thread.h"
#include "error_checking_thread.h"
#include "data_logging_thread.h"

#include "Adafruit_SHT31.h"

USBSerial serial;

DigitalOut status_led(STATUS_LED);

float tempval;
float humval;

int main() {
    Thread::wait(1000);

    sht31_reset();

    Thread analog_read_t(analog_read_thread,NULL,osPriorityNormal,256*4);
    Thread error_checking_t(error_checking_thread,NULL,osPriorityNormal,256*4);
    Thread data_logging_t(data_logging_thread,NULL,osPriorityNormal,256*4);

char * buff;

    while (true) {
        sht31_readTempHum();
        humval = sht31_readHumidity();
        tempval = sht31_readTemperature();

        status_led = !status_led;
        serial.printf("Hello World!\r\n");
        serial.printf("Hum = %f\r\n",humval);

        serial.printf("temp = %f\r\n",tempval);
        Thread::wait(200);
    }
}
