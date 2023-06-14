#include "CLOCK.h"

void generalSetup()
{
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;
	
	RCC->APB1ENR |= (1 << 28);
	PWR->CR |= (1 << 14);
	//activate prefetch buffer but it should already be on
	FLASH->ACR |= (1 << 8) | (1 << 9) | (1 << 10) | (5 << 0);

	// Flash 2 wait state 
	//FLASH->ACR &= (uint32_t)~(0x7); 
	
	
	RCC->CR &= ~(RCC_CR_PLLON);
	
	RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
	
	RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_2;
	
	RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE2_2;
	
	RCC->PLLCFGR = (4 << 0) | (168 << 6) | 0 << 16 | 7 << 24 | 1 << 22;
	
	/*
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_2;
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
	RCC->PLLCFGR |= 168 << RCC_PLLCFGR_PLLN_Pos;
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLP_0;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_Msk;
	RCC->PLLCFGR |= 7 << RCC_PLLCFGR_PLLQ_Pos;		
	*/

	
	
	
	RCC->CR |= RCC_CR_PLLON_Msk;
	while (!(RCC->CR & RCC_CR_PLLRDY)) ;
	
	RCC->CFGR |= 1 << 1;
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) ;
	
	SystemCoreClockUpdate();
	
	RCC->AHB1ENR |= 511;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}