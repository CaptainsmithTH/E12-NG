#include "E12H7.h"

uint8_t	a = 0;
int main(void)
{
	//Warning: if the line below triggers an error, GPIOE is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOE' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;
	
	FLASH->ACR &= ~(0xF);
	FLASH->ACR |= 5;
	
	RCC->CDCFGR1 &= ~(RCC_CDCFGR1_CDCPRE_Msk | RCC_CDCFGR1_CDPPRE_Msk | RCC_CDCFGR1_HPRE_Msk);
	RCC->CDCFGR1 |= 0b100 << RCC_CDCFGR1_CDPPRE_Pos;			//CDCPRE = 1, CDPPRE = 2,HPRE = 1
	RCC->CDCFGR2 &= ~(RCC_CDCFGR2_CDPPRE1_Msk | RCC_CDCFGR2_CDPPRE2_Msk);
	RCC->CDCFGR2 |= 0b100 << RCC_CDCFGR2_CDPPRE1_Pos | 0b100 << RCC_CDCFGR2_CDPPRE2_Pos; //CDCPRE1 = 2, CDCPRE2 = 2
	RCC->SRDCFGR &= ~(RCC_SRDCFGR_SRDPPRE_Msk);
	RCC->SRDCFGR |= 0b100 << RCC_SRDCFGR_SRDPPRE_Pos;
	RCC->PLLCKSELR &= ~(RCC_PLLCKSELR_DIVM1_Msk);
	RCC->PLLCKSELR |= 5 << RCC_PLLCKSELR_DIVM1_Pos;
	RCC->PLL1DIVR &= ~(RCC_PLL1DIVR_N1_Msk);
	RCC->PLL1DIVR |= 112 << RCC_PLL1DIVR_N1_Pos;
	
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN;
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
	pinMode(GPIOE, 3, OUTPUT);
	pinMode(GPIOB, 9, INPUT);
	pinPull(GPIOB, 9, PULLUP);

	for (;;)
	{
		for (uint32_t i = 0; i < 1000000; i++) ;
		pinToggle(GPIOE, 3);
	}
}