
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/f4/nvic.h>

/* Timer clock frequency [Hz] */
#define TIM_CLOCK_FREQ_HZ                   1000000 /* 1MHz */

/* Default PWM frequency */
#define TIM_DEFAULT_PWM_FREQ_HZ             100 /* 100Hz */
/* Maximum PWM frequency */
#define PWM_MAX_FREQ_HZ                 100000  /* 100kHz */

/* Store current PWM frequency */
static uint32_t current_timer_cnt_period;


void init_pwm_timer(enum rcc_periph_clken clken, uint32_t pwm_freq) {
    // Enable Timer clock.
    rcc_periph_clock_enable(clken);
    // Reset clken peripheral
    timer_reset(clken);
    // Set the timers global mode to:
    // - use no divider
    // - alignment edge
    // - count direction up
    timer_set_mode(clken,
                    TIM_CR1_CKD_CK_INT,
                    TIM_CR1_CMS_EDGE,
                    TIM_CR1_DIR_UP);

    // set prescaler
    timer_set_prescaler(clken, 0);
    // enable preload
    timer_enable_preload(clken);
    // set continuous mode
    timer_continuous_mode(clken);
    // set repetition counter
    timer_set_repetition_counter(clken, 0);
    // set period
    timer_set_period(clken, 1024 - 1);


    /* if requested frequency is lower than
     * timer clock frequency */
    if (pwm_freq <= PWM_MAX_FREQ_HZ) {
        /* set period and store it */
        current_timer_cnt_period = ((TIM_CLOCK_FREQ_HZ / pwm_freq) - 1);
        timer_set_period(clken, current_timer_cnt_period);
    }




    /* Init output channels */

    /* Enable GPIOD clock */
    rcc_periph_clock_enable(RCC_GPIOD);

    /* Set GPIO12, GPIO13, GPIO14, GPIO15 (in GPIO port D) to Alternate Function */
    gpio_mode_setup(GPIOD,
                    GPIO_MODE_AF,
                    GPIO_PUPD_NONE,
                    GPIO12 | GPIO13 | GPIO14 | GPIO15);

    /* Push Pull, Speed 50 MHz */
    gpio_set_output_options(GPIOD,
                            GPIO_OTYPE_PP,
                            GPIO_OSPEED_50MHZ,
                            GPIO12 | GPIO13 | GPIO14 | GPIO15);

    /* Alternate Function: clken CH1/2/3/4 */
    gpio_set_af(GPIOD,
                GPIO_AF2,
                GPIO12 | GPIO13 | GPIO14 | GPIO15);

    /* set OC mode for each channel */
    timer_set_oc_mode(clken, TIM_OC1, TIM_OCM_PWM1);
    timer_set_oc_mode(clken, TIM_OC2, TIM_OCM_PWM1);
    timer_set_oc_mode(clken, TIM_OC3, TIM_OCM_PWM1);
    timer_set_oc_mode(clken, TIM_OC4, TIM_OCM_PWM1);

    timer_enable_oc_preload(clken, TIM_OC1);
    timer_enable_oc_preload(clken, TIM_OC2);
    timer_enable_oc_preload(clken, TIM_OC3);
    timer_enable_oc_preload(clken, TIM_OC4);

    /* reset OC value for each channel */
    timer_set_oc_value(clken, TIM_OC1, 0);
    timer_set_oc_value(clken, TIM_OC2, 0);
    timer_set_oc_value(clken, TIM_OC3, 0);
    timer_set_oc_value(clken, TIM_OC4, 0);

    /* enable OC output for each channel */
    timer_enable_oc_output(clken, TIM_OC1);
    timer_enable_oc_output(clken, TIM_OC2);
    timer_enable_oc_output(clken, TIM_OC3);
    timer_enable_oc_output(clken, TIM_OC4);


    // START
    timer_generate_event(clken, TIM_EGR_UG);
    timer_enable_counter(clken);
}


/* set DC value for a channel */
void pwm_set_dc(enum rcc_periph_clken clken, uint8_t ch_index, uint16_t dc_value_permillage){
    uint32_t dc_tmr_reg_value;

    if (dc_value_permillage <= 1000) {
        /* calculate DC timer register value */
        dc_tmr_reg_value = (uint32_t)(((uint64_t)current_timer_cnt_period * dc_value_permillage) / 1000);
        /* update the required channel */
        switch(ch_index) {
        case 0: {
            timer_set_oc_value(clken, TIM_OC1, dc_tmr_reg_value);
            break;
            }
        case 1: {
            timer_set_oc_value(clken, TIM_OC2, dc_tmr_reg_value);
            break;
            }
        case 2: {
            timer_set_oc_value(clken, TIM_OC3, dc_tmr_reg_value);
            break;
            }
        case 3: {
            timer_set_oc_value(clken, TIM_OC4, dc_tmr_reg_value);
            break;
            }
        default: {// wrong channel index: do nothing
            }
        }
    }
}
