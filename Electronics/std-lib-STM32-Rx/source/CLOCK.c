#include "CLOCK.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32f10x.h"



void set_Max_Frequency(void){
	
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	 //activate prefetch buffer but it should already be on
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	// Flash 2 wait state 
	//FLASH->ACR &= (uint32_t)~(0x7);
	FLASH->ACR |= (uint32_t)0x2;   
	
	RCC->CR &= ~(RCC_CR_PLLON);
	RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;
	RCC->CFGR |= RCC_CFGR_PLLSRC;
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	
	RCC->CFGR |= 1<<1;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
	
	SystemCoreClockUpdate();
}


void general_Setup(void){
	set_Max_Frequency();
	GPIOA_ENABLE;
	GPIOB_ENABLE;
	GPIOC_ENABLE;
	GPIOD_ENABLE;
	GPIOE_ENABLE;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

void timer_Setup(void){
	TIM1_ENABLE;
	TIM2_ENABLE;
	TIM3_ENABLE;
	TIM4_ENABLE;
}

