#include "source/SETUP.h"

int main(void)
{
	general_Setup();
	pinMode(GPIOC, 12, OUTPUT50, PUSHPULL);
	//Warning: if the line below triggers an error, GPIOC is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOC' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 
	

	for (;;)
	{
		for (uint32_t i = 0; i < 2000000; i++) ;
		pinToggle(GPIOC, 12);
	}
}
