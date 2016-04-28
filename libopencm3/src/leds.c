#include <specific.h>

#include "alarms_and_delay.h"

void init_leds() {
    rcc_periph_clock_enable(RCC_GPIOD);

    // Set GPIO12-15 (in GPIO port D) to 'output push-pull' for leds.
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
        GPIO12 | GPIO13 | GPIO14 | GPIO15);
}


void led_verte_on() {
    gpio_set(GPIOD, GPIO12);
}
void led_verte_off() {
    gpio_clear(GPIOD, GPIO12);
}

void set_all_led() {
    gpio_set(GPIOD, GPIO12
                  | GPIO13
                  | GPIO14
                  | GPIO15 );
}
void clear_all_led() {
    gpio_clear(GPIOD, GPIO12
                    | GPIO13
                    | GPIO14
                    | GPIO15 );
}


#define LED_DELAY 100
void test_led() {
    gpio_set(GPIOD, GPIO12);
    delay_ms(LED_DELAY);
    gpio_set(GPIOD, GPIO13);
    delay_ms(LED_DELAY);
    gpio_toggle(GPIOD, GPIO12 | GPIO14);
    delay_ms(LED_DELAY);
    gpio_toggle(GPIOD, GPIO13 | GPIO15);
    delay_ms(LED_DELAY);
    gpio_toggle(GPIOD, GPIO14 | GPIO12);
    delay_ms(LED_DELAY);
    gpio_clear(GPIOD, GPIO15);
    delay_ms(LED_DELAY);
    gpio_clear(GPIOD, GPIO12);
    delay_ms(LED_DELAY);
}
