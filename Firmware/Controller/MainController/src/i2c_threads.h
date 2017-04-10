#ifndef I2C_THREADS_H
#define I2C_THREADS_H

#define MOTOR_I2C_ADDRESS 0x03
void motor_command_thread(void const *args);
int get_motor_current(void);
int get_batery_volts(void);

#define LED_INDICATOR_ADDRESS 0x01
void set_indicator_leds_thread(void const *args);
void set_indicator_leds(int val);
int get_indicator_leds(void);

#define FAN_CONTROL_BOARD_ADDRESS 0x02
void fan_control_board_thread(void const *args);
void set_fan_pwr_status(char val);
float get_fctemp(void);
bool get_fan_status(void);

void sht31_readtemphum_thread(void const *args);
float sht31_readTemperature(void);
float sht31_readHumidity(void);

#define DS3231_ADDRESS 0x68
void ds3231_thread(void const *args);
char * get_time(void);

#endif
