
#include "source/STM32_Rx.h"


uint32_t counter = 0;
int main(void)
{
	general_Setup();
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	pinMode(GPIOB, 12, OUTPUT50, PUSHPULL);
	
	//SPI2->CR2 |= SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN;
	/*
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->CR1 |= TIM_CR1_ARPE;
	TIM2->CR2 = 0;
	
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CNT = 0;
	TIM2->EGR = 0;
	TIM2->EGR |= TIM_EGR_UG;
	TIM2->DIER = 0;
	TIM2->SMCR = 0;
	TIM2->ARR = 10;
	TIM2->CCR1 = 5;
	TIM2->PSC = 0;
	TIM2->CR1 |= TIM_CR1_CEN;		 */
	
	
	pinMode(GPIOA, 0, OUTPUT2,ALTPUSHPULL);
	
	while (true)
	{
		pinToggle(GPIOB, 12);
	}
	//Warning: if the line below triggers an error, GPIOC is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOC' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 
	
}