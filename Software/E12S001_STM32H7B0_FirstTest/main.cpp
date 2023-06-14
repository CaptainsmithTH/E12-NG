#include <stm32h7xx_ll_bus.h>
#include <stm32h7xx_ll_gpio.h>
#include <stm32h7xx_ll_utils.h>

int main(void)
{
	LL_InitTick(16000000, 1000);

	//Warning: if the line below triggers an error, GPIOE is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOE' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODE3_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE3_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_Msk;
	NVIC_EnableIRQ(SPI1_IRQn);
	

	for (;;)
	{
		GPIOE->ODR &= ~(1 << 3);
		LL_mDelay(500);
		GPIOE->ODR |= (1 << 3);
		LL_mDelay(500);
	}
}
