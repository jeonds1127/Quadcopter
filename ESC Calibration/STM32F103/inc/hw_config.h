#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* includes */

#include "stm32f10x.h"
#include "stdio.h" // printf Enable
#include "debug.h"
#include <math.h>

// UART configuration ...
#define RCC_APB2Periph_GPIO_USART           RCC_APB2Periph_GPIOA

#define GPIO_USART           GPIOA

#define GPIO_USART_Rx_Pin    GPIO_Pin_10
#define GPIO_USART_Tx_Pin    GPIO_Pin_9

#define WRITE 0
#define READ  1

/* functions */
void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART1_Init(void);
uint8_t USART_GetCharacter(USART_TypeDef *  usart_p);

void delay_ms(__IO uint32_t nTime);
void delay_10us(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif  /*__HW_CONFIG_H */
