#include "CLOCK.h"

uint8_t RCC_HSE_Enable()
{
	RCC->CR |= RCC_CR_HSEON; //ENABLE HSE
	uint32_t timeOutCounter = 0; 
	while (!(RCC->CR & RCC_CR_HSERDY_Msk))
	{
		timeOutCounter++;
		if (timeOutCounter > timeOut)
		{
			return E12_TIMEOUT;
		}
	}
	
	return 0;
}

void RCC_HSE_CSS_Enable()
{
	RCC->CR |= RCC_CR_CSSHSEON;
}

void RCC_AXI_Enable()
{
	RCC->CKGAENR = 0xFFFFFFFF;
}
