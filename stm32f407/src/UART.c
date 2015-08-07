#include <UART.h>
#include <string.h>

void USART3_IRQHandler(void)//cf. startup_stm32f407xx.s
{
	HAL_UART_IRQHandler(&UART_Asser);
}

void UART4_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UART_HandleStructure_T);
}


void Error_UART(){
	reset_all_led();
	while (1) {
		Delay(500);
		HAL_GPIO_TogglePin(GPIOD, LED_ROUGE);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	tmp_bfr_test_UART = *RX_bfr_test_UART;
}

//void UART_handler_

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
}




void init_UART_Xbee(UART_HandleTypeDef *UART_HandleStructure) {
	
	__UART4_CLK_ENABLE();
	
		
	/*##-3- Configure the NVIC for UART ########################################*/
	HAL_NVIC_SetPriority(UART4_IRQn, 4, 4);
	HAL_NVIC_EnableIRQ(UART4_IRQn);
	
	
	//Configuration de l'UART d'émission
	UART_HandleStructure->Init.BaudRate = 115200;//1;//4095
	UART_HandleStructure->Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure->Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure->Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure->Init.Mode = UART_MODE_TX_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure->Init.OverSampling = UART_OVERSAMPLING_8;
	UART_HandleStructure->Instance = UART4;
	
	
	
	//HAL_UART_Init(UART_HandleStructure);
	if(HAL_UART_Init(UART_HandleStructure) != HAL_OK)
	{
		Error_UART();
	}
	
	
	//AF7 : Pin A0 : USART4_TX
	__GPIOC_CLK_ENABLE();
	
	
	//Configuration du pin de transmission
    GPIO_InitTypeDef GPIO_InitStructure_UART;

    GPIO_InitStructure_UART.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStructure_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_UART.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_UART.Pull = GPIO_PULLUP;
    GPIO_InitStructure_UART.Alternate = GPIO_AF8_UART4;
    
    //Configure this pin in Alternate function mode
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure_UART);
	
}

void init_UART_Asser(UART_HandleTypeDef *UART_HandleStructure) {
	
	__USART3_CLK_ENABLE(); //cf. stm32f4xx_hal_rcc_ex.h
	
		
	//##-3- Configure the NVIC for UART ########################################
	HAL_NVIC_SetPriority(USART3_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	
	
	//Configuration de l'UART d'émission
	UART_HandleStructure->Init.BaudRate = 115200;//1;//4095
	UART_HandleStructure->Init.WordLength = UART_WORDLENGTH_8B;
	UART_HandleStructure->Init.StopBits = UART_STOPBITS_1;
	UART_HandleStructure->Init.Parity = UART_PARITY_NONE; //ou UART_PARITY_EVEN ou UART_PARITY_ODD
	UART_HandleStructure->Init.Mode = UART_MODE_TX_RX; // ou UART_MODE_RX ou UART_MODE_TX_RX
	UART_HandleStructure->Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_HandleStructure->Init.OverSampling = UART_OVERSAMPLING_8;
	UART_HandleStructure->Instance = USART3; // cf. stm32f407xx.h
	
	
	
	//HAL_UART_Init(UART_HandleStructure);
	if(HAL_UART_Init(UART_HandleStructure) != HAL_OK)
	{
		Error_UART();
	}
	
	
	//AF7 : Pin D8 : USART3_TX
	__GPIOD_CLK_ENABLE();
	
	
	//Configuration du pin de transmission
    GPIO_InitTypeDef GPIO_InitStructure_UART;

    GPIO_InitStructure_UART.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStructure_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure_UART.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStructure_UART.Pull = GPIO_NOPULL;
    GPIO_InitStructure_UART.Alternate = GPIO_AF7_USART3;//cf. stm32f4xx_hal_gpio_ex.h
    
    //Configure this pin in Alternate function mode
    HAL_GPIO_Init(GPIOD, &GPIO_InitStructure_UART);
	
}




///////////////////////////////

void UART_send_message(const char* message, int longueur) {
	//TODO À vérifier
	if (HAL_UART_Transmit_IT(&UART_Asser, message, longueur) != HAL_OK)
		Error_UART();
	Delay(100);
}

void UART_send_message_xbee(const char* message, int longueur) {
	//TODO À vérifier
	if (HAL_UART_Transmit_IT(&UART_Xbee, message, longueur) != HAL_OK)
		Error_UART();
	Delay(100);
}