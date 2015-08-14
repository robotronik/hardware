#include "PWM.h"

//TODO : remplacer 20000 (période pour les PWM) par la macro qui convient ;)

//C'est dégueulasse parce que on ne peut générer que un pwm de rapp cyclique de 1 avec
//start_PWM d'où l'utilisation de stop_PWM
//du coup : TODO : à revoir en temps de "pas coupe"
void start_PWM(s_PWM *PWMX, uint32_t rapport_cyclique) {
    uint32_t pulse = rapport_cyclique*20-1; // 2 = 20000/1000 (20000 étant la période)
    PWMX->TIM_OC_InitStructure.Pulse = pulse;
    HAL_TIM_PWM_ConfigChannel(&(PWMX->TIM_HandleStructure), &(PWMX->TIM_OC_InitStructure), PWMX->Channel);
    HAL_TIM_PWM_Start(&(PWMX->TIM_HandleStructure), PWMX->Channel);
}

void stop_PWM(s_PWM *PWMX) {
    PWMX->TIM_OC_InitStructure.Pulse = 0;
    HAL_TIM_PWM_ConfigChannel(&(PWMX->TIM_HandleStructure), &(PWMX->TIM_OC_InitStructure), PWMX->Channel);
    HAL_TIM_PWM_Start(&(PWMX->TIM_HandleStructure), PWMX->Channel);
}


void init_pwm(s_PWM *servoX, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {

    //Configuration des pins
    GPIO_InitTypeDef GPIO_InitStructure_PinPWM;


    GPIO_InitStructure_PinPWM.Pin = GPIO_Pin;
    GPIO_InitStructure_PinPWM.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_PinPWM.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_PinPWM.Pull = GPIO_PULLUP;

    if(GPIOx == GPIOA) {
        __GPIOA_CLK_ENABLE();
        switch (GPIO_Pin) {
            case GPIO_PIN_0 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM5;
                servoX->TIM_HandleStructure.Instance = TIM5;
                servoX->Channel = TIM_CHANNEL_1;
                __TIM5_CLK_ENABLE();
                break;
            case GPIO_PIN_1 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF1_TIM2;
                servoX->TIM_HandleStructure.Instance = TIM2;
                servoX->Channel = TIM_CHANNEL_2;
                __TIM2_CLK_ENABLE();
                break;
            case GPIO_PIN_2 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF1_TIM2;
                servoX->TIM_HandleStructure.Instance = TIM2;
                servoX->Channel = TIM_CHANNEL_3;
                __TIM2_CLK_ENABLE();
                break;
            case GPIO_PIN_3 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF1_TIM2;
                servoX->TIM_HandleStructure.Instance = TIM2;
                servoX->Channel = TIM_CHANNEL_4;
                __TIM2_CLK_ENABLE();
                break;
            case GPIO_PIN_6 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_1;
                __TIM3_CLK_ENABLE();
                break;
            case GPIO_PIN_7 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_2;
                __TIM3_CLK_ENABLE();
                break;
            case GPIO_PIN_15 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF1_TIM2;
                servoX->TIM_HandleStructure.Instance = TIM2;
                servoX->Channel = TIM_CHANNEL_1;
                __TIM2_CLK_ENABLE();
                break;
            default:
                mapping_error();
                break;
        }
    } else if (GPIOx == GPIOB) {
        __GPIOB_CLK_ENABLE();
        switch (GPIO_Pin) {
            case GPIO_PIN_0 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_3;
                __TIM3_CLK_ENABLE();
                break;
            case GPIO_PIN_1 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_4;
                __TIM3_CLK_ENABLE();
                break;
            case GPIO_PIN_3 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF1_TIM2;
                servoX->TIM_HandleStructure.Instance = TIM2;
                servoX->Channel = TIM_CHANNEL_2;
                __TIM2_CLK_ENABLE();
                break;
            case GPIO_PIN_4 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_1;
                __TIM3_CLK_ENABLE();
                break;
            case GPIO_PIN_5 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_2;
                __TIM3_CLK_ENABLE();
                break;
            case GPIO_PIN_6 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_1;
                __TIM4_CLK_ENABLE();
                break;
            case GPIO_PIN_7 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_2;
                __TIM4_CLK_ENABLE();
                break;
            case GPIO_PIN_8 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_3;
                __TIM4_CLK_ENABLE();
                break;
            case GPIO_PIN_9 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_4;
                __TIM4_CLK_ENABLE();
                break;
            case GPIO_PIN_10 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF1_TIM2;
                servoX->TIM_HandleStructure.Instance = TIM2;
                servoX->Channel = TIM_CHANNEL_3;
                __TIM2_CLK_ENABLE();
                break;
            case GPIO_PIN_11 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF1_TIM2;
                servoX->TIM_HandleStructure.Instance = TIM2;
                servoX->Channel = TIM_CHANNEL_4;
                __TIM2_CLK_ENABLE();
                break;
            default:
                mapping_error();
                break;
        }
    } else if (GPIOx == GPIOC) {
        __GPIOC_CLK_ENABLE();
        __TIM3_CLK_ENABLE();
        switch (GPIO_Pin) {

            case GPIO_PIN_6 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_1;
                break;
            case GPIO_PIN_7 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_2;
                break;
            case GPIO_PIN_8 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_3;
                break;
            case GPIO_PIN_9 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM3;
                servoX->TIM_HandleStructure.Instance = TIM3;
                servoX->Channel = TIM_CHANNEL_4;
                break;
            default:
                mapping_error();
                break;
        }

    } else if (GPIOx == GPIOD) {
        __GPIOD_CLK_ENABLE();
        __TIM4_CLK_ENABLE();
        switch (GPIO_Pin) {
            case GPIO_PIN_12 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_1;
                break;
            case GPIO_PIN_13 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_2;
                break;
            case GPIO_PIN_14 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_3;
                break;
            case GPIO_PIN_15 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM4;
                servoX->TIM_HandleStructure.Instance = TIM4;
                servoX->Channel = TIM_CHANNEL_4;
                break;
            default:
                mapping_error();
                break;
        }
    } else if (GPIOx == GPIOH) {
        __GPIOH_CLK_ENABLE();
        __TIM5_CLK_ENABLE();
        switch (GPIO_Pin) {
            case GPIO_PIN_10 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM5;
                servoX->TIM_HandleStructure.Instance = TIM5;
                servoX->Channel = TIM_CHANNEL_1;
                break;
            case GPIO_PIN_11 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM5;
                servoX->TIM_HandleStructure.Instance = TIM5;
                servoX->Channel = TIM_CHANNEL_2;
                break;
            case GPIO_PIN_12 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM5;
                servoX->TIM_HandleStructure.Instance = TIM5;
                servoX->Channel = TIM_CHANNEL_3;
                break;
            default:
                mapping_error();
                break;
        }
    } else if (GPIOx == GPIOI) {
        __GPIOI_CLK_ENABLE();
        __TIM5_CLK_ENABLE();
        switch (GPIO_Pin) {
            case GPIO_PIN_0 :
                GPIO_InitStructure_PinPWM.Alternate = GPIO_AF2_TIM5;
                servoX->TIM_HandleStructure.Instance = TIM5;
                servoX->Channel = TIM_CHANNEL_4;
                break;
            default:
                mapping_error();
                break;
        }
    } else {
        mapping_error();
    }

    HAL_GPIO_Init(GPIOx, &GPIO_InitStructure_PinPWM);

    //INITIALISATION du TIMER
    TIM_Base_InitTypeDef TIM_Base_InitStructure;
    uint32_t PrescalerValue = 0;
    uint32_t Timer_Frequency = 1000000;

    // Compute the prescaler value
    PrescalerValue = (uint32_t) ((SystemCoreClock) / Timer_Frequency) - 1;
    TIM_Base_InitStructure.Prescaler = PrescalerValue;
    TIM_Base_InitStructure.Period = 20000 - 1;
    TIM_Base_InitStructure.CounterMode = TIM_COUNTERMODE_UP;
    TIM_Base_InitStructure.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    servoX->TIM_HandleStructure.Init = TIM_Base_InitStructure;
    servoX->TIM_HandleStructure.Channel = servoX->Channel;
    HAL_TIM_Base_Init(&(servoX->TIM_HandleStructure));


    //INITIALISATION PWM
    //TIM_OC_InitTypeDef TIM_OC_InitStructure;
    //PWM mode 1
    servoX->TIM_OC_InitStructure.OCMode = TIM_OCMODE_PWM1;
    //Durée de la pulsation
    servoX->TIM_OC_InitStructure.Pulse = 1500;
    //Actif à l'état haut
    servoX->TIM_OC_InitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
    servoX->TIM_OC_InitStructure.OCFastMode = TIM_OCFAST_ENABLE;
    //HAL_TIM_PWM_Init(&TIM_HandleStructure);
    HAL_TIM_PWM_ConfigChannel(&(servoX->TIM_HandleStructure), &(servoX->TIM_OC_InitStructure), servoX->Channel);
    //Avtication du périphérique timer pour génération de PWM
    HAL_TIM_PWM_Start(&(servoX->TIM_HandleStructure), servoX->Channel);
    //HAL_TIM_PWM_Start_IT(&TIM_HandleStructure, TIM_CHANNEL_4);

}

