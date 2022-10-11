#include "source/E12_STM32_Rx.h"
uint32_t reg = 0;
int main(void)
{

	//Warning: if the line below triggers an error, GPIOC is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOC' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 
	
	
	
	//general_Setup();
	
	GPIOA->CRH = 0;
	GPIOA->CRH |= (1 << 1) | (1 << 0);
	reg = GPIOA->CRH;
	
	while (true) 
	{
		GPIOA->BSRR |= GPIO_BSRR_BS8;
		GPIOA->BSRR |= GPIO_BSRR_BR8;
		reg = GPIOA->CRH;
	}
	
}
