#include "specific.h"
#include <alarms_and_delay.h>

// monotonically increasing number of milliseconds from reset
// overflows every 49 days if you're wondering
volatile uint32_t system_millis;

// Set up a timer to create 1mS ticks.
void systick_setup(void) {
    // clock rate / 1000 to get 1mS interrupt rate
    systick_set_reload(168000);
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();
    // this done last
    systick_interrupt_enable();
}
void init_alarms_and_delay(){
    systick_setup();
}


// sleep for delay milliseconds
void delay_ms(int delay) {
    uint32_t wake = system_millis + (uint32_t)delay;
    while (wake > system_millis);
}



typedef struct {
    uint32_t time_millis;
    void (*callback) (void);
    bool repeat;
    uint32_t repeat_tempo;
} alarm;

alarm alarms[MAX_ALARMS];
int alarm_count = 0;

void add_alarm(int time_millis, void (*callback) (void), bool repeat) {
    alarms[alarm_count].time_millis = system_millis + time_millis;
    alarms[alarm_count].callback = callback;
    alarms[alarm_count].repeat = repeat;
    alarms[alarm_count].repeat_tempo = time_millis;

    alarm_count ++;
}


// Called when systick fires
void sys_tick_handler(void) {
    system_millis++;

    for (int i = 0; i < alarm_count; ++i) {
        if (alarms[i].time_millis == system_millis
        &&  alarms[i].callback) {
            if (alarms[i].repeat) {
                alarms[i].time_millis += alarms[i].repeat_tempo;
            }
            alarms[i].callback();
        }
    }
}

