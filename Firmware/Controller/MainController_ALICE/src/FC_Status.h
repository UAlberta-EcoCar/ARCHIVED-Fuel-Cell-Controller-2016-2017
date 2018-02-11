#ifndef FC_STATUS_H
#define FC_STATUS_H

//signals that send messages between threads
#define IDLE_STATE 0
#define START_STATE 3
#define STOP_STATE 1
#define RUN_STATE 6
#define CHARGE_STATE 5

int get_fc_status(void);
void set_fc_status(int val);

#endif
