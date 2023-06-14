#include "CLOCK.h"

uint8_t HSE_Enable()
{
	RCC->CR |= RCC_CR_HSEON; //ENABLE HSE
	for (uint8_t i = 0; i < 240; i++) ; //Wait
	if (!(RCC->CR & RCC_CR_HSERDY_Msk))
	{
		return 1;
	}
	
	return 0;
}
