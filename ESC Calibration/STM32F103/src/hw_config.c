/* includes */

#include "hw_config.h"
#include "stm32f10x_tim.h"

 
/* global variables */
static volatile uint32_t TimingDelay;

/* functions */
void delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime * 100; // 10 us * nTime * 100 -> 1ms * nTime

  while(TimingDelay != 0);
}

void delay_10us(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

/* defines */
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART1_Init(void)
{
    USART_InitTypeDef USART_InitStructure;
    
    /* USARTx configuration ------------------------------------------------------*/
    /* USARTx configured as follow:
     - BaudRate = 115200 baud  
     - Word Length = 8 Bits
     - One Stop Bit
     - No parity
     - Hardware flow control disabled (RTS and CTS signals)
     - Receive and transmit enabled
     */

    USART_InitStructure.USART_BaudRate   = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;
    USART_InitStructure.USART_Parity     = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl
                                         = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
   
    /* Configure the USARTx */ 
    USART_Init(USART1, &USART_InitStructure);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* Enable the USART1 */
    USART_Cmd(USART1, ENABLE);
}

void Motor_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  													
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* TIM4 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 20000 - 1;     
  TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;  
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = 0;

  TIM_OC3Init(TIM4, &TIM_OCInitStructure);  
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);  

  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);           

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);
  
  /* TIM3 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 20000 - 1;    
  TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;  
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = 0;

  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
  
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void RCC_Configuration(void)
{
    SystemInit(); // 72MHz Enable

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin   = GPIO_USART_Tx_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIO_USART, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin  = GPIO_USART_Rx_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIO_USART, &GPIO_InitStructure);
}

PUTCHAR_PROTOTYPE
{
    /* Write a character to the USART */  
    if( ch == '\n') {
        USART_SendData(USART1, '\r');
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, '\n');
    }else {
        USART_SendData(USART1, (u8) ch);
    }

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return ch;
}

uint8_t USART_GetCharacter(USART_TypeDef *  usart_p)
{
    uint8_t data;

    /* Loop until the end of transmission */
    while(USART_GetFlagStatus(usart_p, USART_FLAG_RXNE) == RESET);

    /* Write a character to the USART */
    data = USART_ReceiveData(usart_p);

    USART_SendData(usart_p, data);
    while(USART_GetFlagStatus(usart_p, USART_FLAG_TXE) == RESET);

    if( data == '\r' )  return (int)('\n');
    else                return(data);
}


