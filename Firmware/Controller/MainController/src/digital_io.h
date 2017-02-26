#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

void supply_valve(bool val);
void purge_valve(bool val);

void start_relay(bool val);
void motor_relay(bool val);
void charge_relay(bool val);
void cap_relay(bool val);
void fcc_relay(bool val);

#endif
