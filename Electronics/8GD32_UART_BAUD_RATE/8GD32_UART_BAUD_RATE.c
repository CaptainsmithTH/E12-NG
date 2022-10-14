#include "source/E12_STM32_Rx.h"

int main(void)
{
	general_Setup();
	
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	
}