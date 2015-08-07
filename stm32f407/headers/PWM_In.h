#ifndef __PWM_IN_H__
#define __PWM_IN_H__

// Encore d'actualité, Ojeme ?
// long int avg;
// int avg_cnt=0;


// // Timer handler declaration 
// TIM_HandleTypeDef        TimHandle;
// // Timer Input Capture Configuration Structure declaration 
// TIM_IC_InitTypeDef       sConfig;

// // Slave configuration structure 
// TIM_SlaveConfigTypeDef   sSlaveConfig;

// // Captured Value 
// __IO uint32_t            uwIC2Value = 0;
// // Duty Cycle Value 
// __IO uint32_t            uwDutyCycle = 0;
// // Frequency Value 
// __IO uint32_t            uwFrequency = 0;


void Error_PWM_Input();

void init_PWM_In(void);

#include "stm32f4xx_hal_conf.h"
#include "LED.h"
#include "utilities.h"

void activate_sensor1();
void desactivate_sensor1();
void deinit_capteur1();
void activate_sensor2();
void init_sensor1();
void init_sensor2();

void desactivate_sensor2();
void deinit_capteur2();
long int get_value_capt1();
long int get_value_capt2();

void Error_PWM_Input();

#endif
