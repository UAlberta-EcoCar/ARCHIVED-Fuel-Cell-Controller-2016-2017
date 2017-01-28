#include <mbed.h>
#include <rtos.h>


DigitalOut led1(PTC5);
DigitalOut led2(PTD1);
DigitalOut led3(PTC7);

void led2_thread(void const *args) {
    while (true) {
        led2 = !led2;
        Thread::wait(300);
    }
}

void led3_thread(void const *args){
  while (true) {
    led3 = !led3;
    Thread::wait(400);
  }
}

int main() {
    //Thread led2_t(led2_thread,NULL,osPriorityNormal,256*4);
    //Thread led3_t(led3_thread,NULL,osPriorityNormal,256*4);

    while (true) {
        led1 = !led1;
        Thread::wait(200);
        //led2_t.terminate(); //kill a thread
    }
}
