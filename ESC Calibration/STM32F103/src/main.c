#include "hw_config.h"

#include <stdio.h>

// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in ¥ìs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in ¥ìs

#define PWM_MOTOR1 TIM4->CCR4 // PB9 
#define PWM_MOTOR2 TIM3->CCR3 // PB0 
#define PWM_MOTOR3 TIM3->CCR4 // PB1 
#define PWM_MOTOR4 TIM4->CCR3 // PB8

/* Global variables */
RCC_ClocksTypeDef  rcc_clocks;

void displayInstructions()
{  
  printf("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :\n");
  printf("\t0 : Send min throttle\n");
  printf("\t1 : Send max throttle\n");
  printf("\t2 : Run test function\n\n");
}

void test()
{   
  for (int i = MIN_PULSE_LENGTH; i <= MAX_PULSE_LENGTH; i += 5) {
    printf("Pulse length = ");
    printf("%d\n",i);
    
    PWM_MOTOR1 = i;
    PWM_MOTOR2 = i;
    PWM_MOTOR3 = i;
    PWM_MOTOR4 = i;
    
    delay_ms(200);
  }
  
  printf("STOP");
  PWM_MOTOR1 = MIN_PULSE_LENGTH;
  PWM_MOTOR2 = MIN_PULSE_LENGTH;
  PWM_MOTOR3 = MIN_PULSE_LENGTH;
  PWM_MOTOR4 = MIN_PULSE_LENGTH;
}

int main(void)
{
  char ch;
  
  /* System Clocks Configuration */
  RCC_Configuration();
  RCC_GetClocksFreq(&rcc_clocks);
  
  /* Setup SysTick Timer for 10usec interrupts */
  if (SysTick_Config(rcc_clocks.SYSCLK_Frequency / 100000))while (1);
  
  /* Configure the GPIO ports */
  GPIO_Configuration();
  
  /* Reset */
  USART1_Init();                  printf("USART : OK\n");
  Motor_Init(); 
  delay_ms(100);
  
  displayInstructions();  
  
  while(1)
  { 
    ch = USART_GetCharacter(USART1);
    switch ((char)ch) {
    // 0
    case '0' : 
      printf("Sending minimum throttle\n");
      PWM_MOTOR1 = MIN_PULSE_LENGTH;
      PWM_MOTOR2 = MIN_PULSE_LENGTH;
      PWM_MOTOR3 = MIN_PULSE_LENGTH;
      PWM_MOTOR4 = MIN_PULSE_LENGTH;
      break;
    
    // 1
    case '1' :
      printf("Sending maximum throttle\n");
      PWM_MOTOR1 = MAX_PULSE_LENGTH;
      PWM_MOTOR2 = MAX_PULSE_LENGTH;
      PWM_MOTOR3 = MAX_PULSE_LENGTH;
      PWM_MOTOR4 = MAX_PULSE_LENGTH;
      break;
    
    // 2
    case '2' : 
      printf("Running test in 3\n");
      delay_ms(1000);
      printf(" 2");
      delay_ms(1000);
      printf(" 1...");
      delay_ms(1000);
      test();
      break;
    }
    ch = 0;
  }  
}