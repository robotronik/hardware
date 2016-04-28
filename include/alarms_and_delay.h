#ifndef HARDWARE_ALARMS_AND_DELAY_H
#define HARDWARE_ALARMS_AND_DELAY_H

#define MAX_ALARMS 10


void init_alarms_and_delay();

void delay_ms(int delay);


// Attention, callback est appelé dans une interruption donc elle ne doit
// pas appeler d'autres interruptions et ne doit pas être longue.
void add_alarm(int time_millis, void (*callback) (void));




#endif
