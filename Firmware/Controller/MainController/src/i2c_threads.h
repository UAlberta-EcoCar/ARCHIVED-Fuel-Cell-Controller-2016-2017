#ifndef I2C_THREADS_H
#define I2C_THREADS_H

void sht31_readtemphum_thread(void const *args);
float sht31_readTemperature(void);
float sht31_readHumidity(void);

#endif
