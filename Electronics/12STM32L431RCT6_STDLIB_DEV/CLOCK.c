#include "CLOCK.h"

void setClock80MHZ()
{
	setClockFrequency(20, 0, 0, 0, 0, 0);
}

void setClock40MHZ()
{
	setClockFrequency(20, 1, 0, 0, 0, 0);
}

void setClockFrequency(uint8_t PLLN, uint8_t PLLM, uint8_t PLLR, uint8_t HPRE, uint8_t PPRE1, uint8_t PPRE2)
{
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;
	//activate prefetch buffer but it should already be on
	FLASH->ACR |= FLASH_ACR_PRFTEN;
	
	// Flash 2 wait state 
	//FLASH->ACR &= (uint32_t)~(0x7);
	FLASH->ACR |= (uint32_t)0x2;   
	
	RCC->CR &= ~(RCC_CR_PLLON);
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE | PLLN << RCC_PLLCFGR_PLLN_Pos | PLLM << RCC_PLLCFGR_PLLM_Pos;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN | PLLR << RCC_PLLCFGR_PLLR_Pos;
	RCC->PLLCFGR &= ~(PLLN << RCC_PLLCFGR_PLLN_Pos ^ RCC_PLLCFGR_PLLN_Msk);
	RCC->PLLCFGR &= ~(PLLM << RCC_PLLCFGR_PLLM_Pos ^ RCC_PLLCFGR_PLLM_Msk) ;
	RCC->PLLCFGR &= ~(PLLR << RCC_PLLCFGR_PLLR_Pos ^ RCC_PLLCFGR_PLLR_Msk);
	RCC->CFGR |= HPRE << RCC_CFGR_HPRE_Pos | PPRE1 << RCC_CFGR_PPRE1_Pos | PPRE2 << RCC_CFGR_PPRE2_Pos;
	RCC->CFGR &= ~(HPRE << RCC_CFGR_HPRE_Pos ^ RCC_CFGR_HPRE_Msk);
	RCC->CFGR &= ~(PPRE1 << RCC_CFGR_PPRE1_Pos ^ RCC_CFGR_PPRE1_Msk);
	RCC->CFGR &= ~(PPRE2 << RCC_CFGR_PPRE2_Pos ^ RCC_CFGR_PPRE2_Msk);
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY)) ;
	
	RCC->CFGR |= RCC_CFGR_SW_1 | RCC_CFGR_SW_0; 
	while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) ;
	
	SystemCoreClockUpdate();
}