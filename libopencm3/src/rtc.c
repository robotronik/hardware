#include <specific.h>
#include <libopencm3/stm32/rtc.h>

void init_RTC() {
    //rtc_auto_awake(RCC_LSE, 0x7fff);

}

void rtc_start_alarm(int time) {
    rtc_set_wakeup_time((uint32_t)time, 0);

    rtc_enable_wakeup_timer();
}


void rtc_isr(void) {
    // The interrupt flag isn't cleared by hardware, we have to do it.
    rtc_clear_wakeup_flag();

    set_all_led();
}
