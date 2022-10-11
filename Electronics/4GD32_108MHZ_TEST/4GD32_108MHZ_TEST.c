#include "source/E12_STM32_Rx.h"

int main(void)
{
	general_Setup();
	pinMode(GPIOC, 13, OUTPUT50, PUSHPULL);
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->CR1 |= TIM_CR1_ARPE;
	TIM2->SMCR = 0;
	TIM2->EGR = 0;
	TIM2->DIER = 0;
	TIM2->CNT = 0;
	TIM2->PSC = 10800;
	TIM2->ARR = 5000;
	TIM2->EGR |= TIM_EGR_UG;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->CR1 |= TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM2_IRQn);
	
	while (true) 
	{
		
	}
}

void TIM2_IRQHandler()
{
	if (TIM2->SR & TIM_SR_UIF)
	{
		TIM2->SR &= ~TIM_SR_UIF;
		pinToggle(GPIOC, 13);
	}
}
