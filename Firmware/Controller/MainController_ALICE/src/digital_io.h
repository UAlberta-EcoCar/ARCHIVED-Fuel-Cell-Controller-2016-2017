#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

bool get_supply_valve();
void supply_valve(bool val);
bool get_purge_valve();
void purge_valve(bool val);

bool get_start_relay();
void start_relay(bool val);
bool get_motor_relay();
void motor_relay(bool val);
bool get_charge_relay();
void charge_relay(bool val);
bool get_cap_relay();
void cap_relay(bool val);
bool get_fcc_relay();
void fcc_relay(bool val);

#endif
