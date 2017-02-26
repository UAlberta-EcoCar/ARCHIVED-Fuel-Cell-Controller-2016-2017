#ifndef ANALOG_READ_THREAD_H
#define ANALOG_READ_THREAD_H

void analog_read_thread(void const *args);

float get_capvolt(void);
float get_fccurr(void);
float get_fcvolt(void);
float get_capcurr(void);
float get_fcpres(void);

double get_fc_coulumbs(void);
double get_fc_joules(void);
double get_cap_coulumbs(void);
double get_cap_joules(void);

#endif
