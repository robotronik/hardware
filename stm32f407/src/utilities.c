#include "utilities.h"

volatile uint32_t time_var1, time_var2;
/*
 * Called from systick handler
 */
void timing_handler() {
    if (time_var1) {
        time_var1--;
    }
    time_var2++;
}

void start_timing(uint32_t duration) {
    time_var1 = duration;
}
int ended_timing() {
    return (time_var1 == 0);
}

/*
 * Delay a number of systick cycles (1ms)
 */
void Delay(volatile uint32_t nCount) {
    time_var1 = nCount;

    while(time_var1){};
}

void SysTick_Handler(void)
{
    timing_handler();
}

ADC_HandleTypeDef   ADC_Structure;


void ADC_IRQHandler(void)//cf. startup_stm32f407xx.s
{
    HAL_ADC_IRQHandler(&ADC_Structure);
}

void ADC_error() {
    while(1) {
        Delay(50);
        HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
    }
}

void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc)
{
    (void)(hadc);
    HAL_GPIO_WritePin(GPIOD, LED_ORANGE, GPIO_PIN_SET);
}
