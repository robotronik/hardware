#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f4xx_hal_conf.h"
#include "LED.h"
#include "error.h"
#include "utilities.h"

int read_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void write_pin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int state);
void init_pin_mode(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,
                	uint32_t io_mode, uint32_t pull_mode);

#endif