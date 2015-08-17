#include "GPIO.h"

int read_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    switch(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)) {
        case GPIO_PIN_RESET :
            return 0;
        case GPIO_PIN_SET :
            return 1;
    }
    mapping_error();
}

void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int state) {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, state);
}

void init_pin_mode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
                    uint32_t io_mode, uint32_t pull_mode) {
    GPIO_InitTypeDef  GPIO_InitStructure;

    // GPIOD Periph clock enable
    if(GPIOx==GPIOA) {
        __GPIOA_CLK_ENABLE();
    } else if(GPIOx==GPIOB) {
        __GPIOB_CLK_ENABLE();
    } else if(GPIOx==GPIOC) {
        __GPIOC_CLK_ENABLE();
    } else if(GPIOx==GPIOD) {
        __GPIOD_CLK_ENABLE();
    } else if(GPIOx==GPIOE) {
        __GPIOE_CLK_ENABLE();
    } else if(GPIOx==GPIOH) {
        __GPIOH_CLK_ENABLE();
    } else if(GPIOx==GPIOI) {
        __GPIOI_CLK_ENABLE();
    }

    GPIO_InitStructure.Pin = GPIO_Pin;
    GPIO_InitStructure.Mode = io_mode;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure.Pull = pull_mode;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void display_PWM_GPIO(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    start_timing(2000);
    while(!ended_timing()) {
        switch ( read_pin(GPIOx,GPIO_Pin)) {
            case 0:
                HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_RESET);
                break;
            case 1:
                HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
                break;
            default:
                HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, LED_ROUGE, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, LED_BLEUE, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, LED_ORANGE, GPIO_PIN_SET);
                break;
        }

    }
}
