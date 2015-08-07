#ifndef __UART_H__
#define __UART_H__

#include "stm32f4xx_hal_conf.h"
#include "LED.h"
#include "utilities.h"

/* UART handler declarations */
UART_HandleTypeDef	UART_HandleStructure_T;
UART_HandleTypeDef	UART_HandleStructure_R;

UART_HandleTypeDef	UART_Asser;//PD8: USART3_TX // PD9:	USART3_RX

UART_HandleTypeDef	UART_Xbee;

void init_UART_Xbee(UART_HandleTypeDef *UART_HandleStructure);
void init_UART_Asser(UART_HandleTypeDef *UART_HandleStructure);
void send_word(UART_HandleTypeDef *UART_HandleStructure, const char *str);
void send_word_IT(UART_HandleTypeDef *UART_HandleStructure, const char *str);

void test_UART_TX_RX();
void bien_recu ();
void pas_recu ();



uint8_t RX_bfr_test_UART[1];
uint8_t tmp_bfr_test_UART;

#endif
