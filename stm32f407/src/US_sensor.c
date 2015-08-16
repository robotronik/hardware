#include "US_sensor.h"
#include "LED.h"

// Timer handler declaration
TIM_HandleTypeDef        TimHandle_sensor1;
TIM_HandleTypeDef        TimHandle_sensor2;

// Timer Input Capture Configuration Structure declaration
TIM_IC_InitTypeDef       sConfig;

// Slave configuration structure
TIM_SlaveConfigTypeDef   sSlaveConfig;

void TIM8_BRK_TIM12_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TimHandle_sensor2);
}

void TIM5_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TimHandle_sensor1);
}

void Error_PWM_Input()
{
	while (1) {
        HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
        HAL_GPIO_TogglePin(GPIOD, LED_ORANGE);
        delay_ms(100);
    }
}
// Captured Value
__IO uint32_t            uwIC2Value_sensor1 = 0;
// Duty Cycle Value
__IO long int            uwDutyCycle_sensor1 = 0;
// Frequency Value
__IO uint32_t            uwFrequency_sensor1 = 0;

void init_sensors() {
	init_sensor1();
	init_sensor1();
}

// Validation et lissage du signal

int sensor1_valeurs_lissage_compteur = 0;
int sensor1_valeurs_lissage_somme    = 0;

int sensor2_valeurs_lissage_compteur = 0;
int sensor2_valeurs_lissage_somme    = 0;

int valide_presence(int *somme, int *compteur, int detection) {
	(*compteur)++;
	(*compteur) %= NB_VALEURS_LISSAGE;

	if (detection < LIMIT_RANGE) {
		// On a détecté quelque chose dans le périmètre !
		(*somme)++;
	}

	if (*compteur == 0) {
		// On a reçu 5 valeurs, on a donc une information pertinente
		if ( (*somme) * 2 > NB_VALEURS_LISSAGE) {
			*somme = 0;
			return ADVERSAIRE_DETECTE;
		}
		else {
			*somme = 0;
			return ADVERSAIRE_NON_DETECTE;
		}
	}
	return ATTENTE_FIN_DETECTION;
}


void init_sensor1()
{
	//PA1 : TIM5_CH2 PIN DE RECEPTION !!!

	/// @brief TIM MSP Initialization
	///        This function configures the hardware resources used in this example:
	///           - Peripheral's clock enable
	///           - Peripheral's GPIO Configuration
	/// @param htim: TIM handle pointer
	/// @retval None

	GPIO_InitTypeDef   GPIO_InitStruct;

	//##-1- Enable peripherals and GPIO Clocks #################################
	// TIMx Peripheral clock enable
	__HAL_RCC_TIM5_CLK_ENABLE();

	// Enable GPIO channels Clock
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Configure  (TIMx_Channel) in Alternate function, push-pull and 100MHz speed
	GPIO_InitStruct.Pin = GPIO_PIN_1;//GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//##-2- Configure the NVIC for TIMx #########################################
	// Sets the priority grouping field
	HAL_NVIC_SetPriority(TIM5_IRQn, 2, 2);

	// Enable the TIM5 global Interrupt
	HAL_NVIC_EnableIRQ(TIM5_IRQn);


	//##-1- Configure the TIM peripheral #######################################
	// Set TIMx instance
	TimHandle_sensor1.Instance = TIM5;

	// Initialize TIMx peripheral as follow:
	//   + Period = 0xFFFF
	//   + Prescaler = 0
	//   + ClockDivision = 0
	//   + Counter direction = Up

	TimHandle_sensor1.Init.Period = 0xFFFF;
	TimHandle_sensor1.Init.Prescaler = 20;
	TimHandle_sensor1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	TimHandle_sensor1.Init.CounterMode = TIM_COUNTERMODE_UP;
	if(HAL_TIM_IC_Init(&TimHandle_sensor1) != HAL_OK)
	{
	// Initialization Error
		Error_PWM_Input();
	}

	//##-2- Configure the Input Capture channels ###############################
	// Common configuration
	sConfig.ICPrescaler = TIM_ICPSC_DIV1;
	sConfig.ICFilter = 0;

	// Configure the Input Capture of channel 1
	sConfig.ICPolarity = TIM_ICPOLARITY_FALLING;
	sConfig.ICSelection = TIM_ICSELECTION_INDIRECTTI;// TIM_ICSELECTION_DIRECTTI, TIM_ICSELECTION_INDIRECTTI or TIM_ICSELECTION_TRC
	if(HAL_TIM_IC_ConfigChannel(&TimHandle_sensor1, &sConfig, TIM_CHANNEL_1) != HAL_OK)
	{
	// Configuration Error
		Error_PWM_Input();
	}

	 //Configure the Input Capture of channel 2
	sConfig.ICPolarity = TIM_ICPOLARITY_RISING;
	sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
	if(HAL_TIM_IC_ConfigChannel(&TimHandle_sensor1, &sConfig, TIM_CHANNEL_2) != HAL_OK)
	{
		//Configuration Error
		Error_PWM_Input();
	}


	//##-3- Configure the slave mode ###########################################
	// Select the slave Mode: Reset Mode
	sSlaveConfig.SlaveMode     = TIM_SLAVEMODE_RESET;
	sSlaveConfig.InputTrigger  = TIM_TS_TI2FP2;
	if(HAL_TIM_SlaveConfigSynchronization(&TimHandle_sensor1, &sSlaveConfig) != HAL_OK)
	{
	// Configuration Error
		Error_PWM_Input();
	}


}


void init_sensor2()
{
	//PA3 : TIM9_CH2 PIN DE RECEPTION !!!

	/// @brief TIM MSP Initialization
	///        This function configures the hardware resources used in this example:
	///           - Peripheral's clock enable
	///           - Peripheral's GPIO Configuration
	/// @param htim: TIM handle pointer
	/// @retval None

	GPIO_InitTypeDef   GPIO_InitStruct;

	//##-1- Enable peripherals and GPIO Clocks #################################
	// TIMx Peripheral clock enable
	__HAL_RCC_TIM12_CLK_ENABLE();

	// Enable GPIO channels Clock
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Configure  (TIMx_Channel) in Alternate function, push-pull and 100MHz speed
	GPIO_InitStruct.Pin = GPIO_PIN_15;//GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_TIM12;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//##-2- Configure the NVIC for TIMx #########################################
	// Sets the priority grouping field
	HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 2, 2);

	// Enable the TIM5 global Interrupt
	HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);


	//##-1- Configure the TIM peripheral #######################################
	// Set TIMx instance
	TimHandle_sensor2.Instance = TIM12;

	// Initialize TIMx peripheral as follow:
	//   + Period = 0xFFFF
	//   + Prescaler = 0
	//   + ClockDivision = 0
	//   + Counter direction = Up

	TimHandle_sensor2.Init.Period = 0xFFFF;
	TimHandle_sensor2.Init.Prescaler = 20;
	TimHandle_sensor2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	TimHandle_sensor2.Init.CounterMode = TIM_COUNTERMODE_UP;
	if(HAL_TIM_IC_Init(&TimHandle_sensor2) != HAL_OK)
	{
	// Initialization Error
		Error_PWM_Input();
	}

	//##-2- Configure the Input Capture channels ###############################
	// Common configuration
	sConfig.ICPrescaler = TIM_ICPSC_DIV1;
	sConfig.ICFilter = 0;

	// Configure the Input Capture of channel 1
	sConfig.ICPolarity = TIM_ICPOLARITY_FALLING;
	sConfig.ICSelection = TIM_ICSELECTION_INDIRECTTI;// TIM_ICSELECTION_DIRECTTI, TIM_ICSELECTION_INDIRECTTI or TIM_ICSELECTION_TRC
	if(HAL_TIM_IC_ConfigChannel(&TimHandle_sensor2, &sConfig, TIM_CHANNEL_1) != HAL_OK)
		Error_PWM_Input();

	 //Configure the Input Capture of channel 2
	sConfig.ICPolarity = TIM_ICPOLARITY_RISING;
	sConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
	if(HAL_TIM_IC_ConfigChannel(&TimHandle_sensor2, &sConfig, TIM_CHANNEL_2) != HAL_OK)
	{
		//Configuration Error
		Error_PWM_Input();
	}


	//##-3- Configure the slave mode ###########################################
	// Select the slave Mode: Reset Mode
	sSlaveConfig.SlaveMode     = TIM_SLAVEMODE_RESET;
	sSlaveConfig.InputTrigger  = TIM_TS_TI2FP2;
	if(HAL_TIM_SlaveConfigSynchronization(&TimHandle_sensor2, &sSlaveConfig) != HAL_OK)
	{
	// Configuration Error
		Error_PWM_Input();
	}


}

void activate_sensor1()
{
	//##-4- Start the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Start_IT(&TimHandle_sensor1, TIM_CHANNEL_2) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}

	//##-5- Start the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Start_IT(&TimHandle_sensor1, TIM_CHANNEL_1) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}
}

void activate_sensor2()
{
	//##-4- Start the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Start_IT(&TimHandle_sensor2, TIM_CHANNEL_2) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}

	//##-5- Start the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Start_IT(&TimHandle_sensor2, TIM_CHANNEL_1) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}
}

void desactivate_sensor1()
{
	//##-4- Stop the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Stop_IT(&TimHandle_sensor1, TIM_CHANNEL_2) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}

	//##-5- Stop the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Stop_IT(&TimHandle_sensor1, TIM_CHANNEL_1) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}
}

void desactivate_sensor2()
{
	//##-4- Stop the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Stop_IT(&TimHandle_sensor2, TIM_CHANNEL_2) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}

	//##-5- Stop the Input Capture in interrupt mode ##########################
	if(HAL_TIM_IC_Stop_IT(&TimHandle_sensor2, TIM_CHANNEL_1) != HAL_OK)
	{
	// Starting Error
		Error_PWM_Input();
	}
}




///
//  * @brief  Input Capture callback in non blocking mode
//  * @param  htim: TIM IC handle
//  * @retval None

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	if(htim == &TimHandle_sensor1)
	{


		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			// Get the Input Capture value
			uwIC2Value_sensor1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

			if (uwIC2Value_sensor1 != 0)
			{
				// Duty cycle computation
				uwDutyCycle_sensor1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);//)) / (uwIC2Value * 2);
				if(uwDutyCycle_sensor1 != 0){

					switch(valide_presence(
							&sensor1_valeurs_lissage_somme,
							&sensor1_valeurs_lissage_compteur,
							uwDutyCycle_sensor1) ) {
						case ADVERSAIRE_DETECTE:
							//HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
						    HAL_GPIO_TogglePin(GPIOD, LED_ORANGE);

							adversaire_detecte_callback();
							break;
						case ADVERSAIRE_NON_DETECTE:
							//HAL_GPIO_TogglePin(GPIOD, LED_VERTE);
							break;
						case ATTENTE_FIN_DETECTION:
							//HAL_GPIO_TogglePin(GPIOD, LED_ORANGE);
							break;
						default:
							//HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
							break;
					}
				}
				// uwFrequency computation
				// TIM4 counter clock = (RCC_Clocks.HCLK_Frequency)/2
				uwFrequency_sensor1 = (HAL_RCC_GetHCLKFreq())/2 / uwIC2Value_sensor1;
			}
			else
			{
				uwDutyCycle_sensor1 = 0;
				uwFrequency_sensor1 = 0;
			}
		}


	}
	else if(htim == &TimHandle_sensor2)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			// Get the Input Capture value
			uwIC2Value_sensor1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

			if (uwIC2Value_sensor1 != 0)
			{
				// Duty cycle computation
				uwDutyCycle_sensor1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);//)) / (uwIC2Value * 2);

				if(uwDutyCycle_sensor1 != 0)
				{

					switch(valide_presence(
							&sensor2_valeurs_lissage_somme,
							&sensor2_valeurs_lissage_compteur,
							uwDutyCycle_sensor1) ) {
						case ADVERSAIRE_DETECTE:
							//HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
						    HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);

							adversaire_detecte_callback();
							break;
						case ADVERSAIRE_NON_DETECTE:
							//HAL_GPIO_TogglePin(GPIOD, LED_VERTE);
							break;
						case ATTENTE_FIN_DETECTION:
							//HAL_GPIO_TogglePin(GPIOD, LED_ORANGE);
							break;
						default:
							//HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
							break;
					}
				}

				// uwFrequency computation
				//TIM4 counter clock = (RCC_Clocks.HCLK_Frequency)/2
				uwFrequency_sensor1 = (HAL_RCC_GetHCLKFreq())/2 / uwIC2Value_sensor1;
			}
			else
			{
				uwDutyCycle_sensor1 = 0;
				uwFrequency_sensor1 = 0;
			}
		}
	}

}

