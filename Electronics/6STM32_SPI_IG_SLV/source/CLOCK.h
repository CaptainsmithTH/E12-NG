#ifndef CLOCK
#define CLOCK
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32f103xe.h"

//DEFINE SECTION
//===================================================

#define GPIOA_ENABLE			RCC->APB2ENR |= (1<<2)
#define GPIOB_ENABLE			RCC->APB2ENR |= (1<<3)
#define GPIOC_ENABLE			RCC->APB2ENR |= (1<<4)
#define GPIOD_ENABLE			RCC->APB2ENR |= (1<<5)
#define GPIOE_ENABLE			RCC->APB2ENR |= (1<<6)
#define AFIO_ENABLE				RCC->APB2ENR |= (1<<0)
#define ADC1_ENABLE				RCC->APB2ENR |= (1<<9)
#define ADC2_ENABLE				RCC->APB2ENR |= (1<<10)

#define SPI1_ENABLE				RCC->APB2ENR |= (1<<12)
#define SPI2_ENABLE				RCC->APB1ENR |= (1<<14)
#define SPI3_ENABLe				RCC->APB1ENR |= (1<<15)
#define USART1_ENABLE			RCC->APB2ENR |= (1<<14)

#define DMA1_ENABLE				RCC->AHBENR |= (1<<0)
#define DMA2_ENABLE				RCC->AHBENR |= (1<<1)

#define TIM1_ENABLE				RCC->APB2ENR |= (1<<11)
#define TIM2_ENABLE				RCC->APB1ENR |= (1<<0)
#define TIM3_ENABLE				RCC->APB1ENR |= (1<<1)
#define TIM4_ENABLE				RCC->APB1ENR |= (1<<2)
#define TIM5_ENABLE				RCC->APB1ENR |= (1<<3)
#define TIM6_ENABLE				RCC->APB1ENR |= (1<<4)
#define TIM7_ENABLE				RCC->APB1ENR |= (1<<5)



//FUNCTION


void set_Max_Frequency(void);
//REQUIRE EXTERNAL 8MHZ CRYSTAL
//WILL OUTPUT
//72MHZ		SYSCLK
//72MHZ		APB2
//36MHZ		APB1

void general_Setup(void);
//Max Frequency
//Enable all GPIO Clock

void timer_Setup(void);
//Max Frequency
//Enable all Timer Clock


#endif

