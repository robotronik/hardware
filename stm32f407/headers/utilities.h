#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "stm32f4xx_hal_conf.h"

void start_timing(uint32_t duration);
int ended_timing();

void Delay(volatile uint32_t nCount);//Delays nCount ms
void init();

#endif
