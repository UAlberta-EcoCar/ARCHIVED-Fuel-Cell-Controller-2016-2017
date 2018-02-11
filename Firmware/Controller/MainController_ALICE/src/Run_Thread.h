#ifndef RUN_THREAD_H
#define RUN_THREAD_H

#define PURGE_THRES 2300.0f
#define PURGE_TIME 200

#define VOLTAGE_THRESHOLD 65.0f //Changed from 35.0f

void run_thread(void const *args);
int get_purge_count(void);

#endif
