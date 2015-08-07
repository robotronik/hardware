#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f4xx_hal_conf.h"
#include "error.h"

typedef struct
{

    TIM_HandleTypeDef	TIM_HandleStructure;
    TIM_OC_InitTypeDef	TIM_OC_InitStructure;
    uint32_t			Channel;

} s_PWM;

void start_PWM(s_PWM *PWMX, uint32_t rapport_cyclique);
void init_pwm(s_PWM *servoX, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void stop_PWM(s_PWM *PWMX);

#endif


