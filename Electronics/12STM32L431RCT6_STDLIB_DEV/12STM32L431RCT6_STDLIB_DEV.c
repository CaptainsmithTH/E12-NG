#include "GPIO.h"
#include "CLOCK.h"

uint8_t lightConfig[20][5];
uint32_t counter = 0;
int main(void)
{
	setClock80MHZ();
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	/*
	SPI2->CR1 |= SPI_CR1_BR_0;
	SPI2->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2 | SPI_CR2_TXDMAEN;
	SPI2->CR1 |= SPI_CR1_SPE;
	
	DMA1_Channel5->CMAR = (uint32_t)lightConfig;
	DMA1_Channel5->CPAR = (uint32_t)&SPI2->DR;
	DMA1_Channel5->CNDTR = 5;
	DMA1_Channel5->CCR |= DMA_CCR_DIR | DMA_CCR_TCIE | DMA_CCR_MINC;   
	
	for (uint8_t i = 0; i < 20; i++)
	{
		for (uint8_t j = 0; j < 5; j++)
		{
			lightConfig[i][j] = 0x255 - i;
		}
	}
			*/
	
	TIM2->DIER = 0;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->ARR = 10000;
	TIM2->PSC = 7999;
	TIM2->SMCR = 0;
	TIM2->CR2 = 0;
	TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM2_IRQn);
	/*
	NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	
	GPIOB->AFR[1] |= 5 << 16 | 5 << 20 | 5 << 28;
	
				  */
	
	pinMode(GPIOC, 13, OUTPUT, PUSHPULL);
	pinMode(GPIOB, 15, OUTPUT, PUSHPULL);
	pinMode(GPIOB, 13, OUTPUT, PUSHPULL);
	pinMode(GPIOB, 12, OUTPUT, PUSHPULL);
	GPIOB->ODR |= (1 << 12);
	for (;;)
	{	/*
		
		pinWrite(GPIOC, 13, LOW);
		for (uint32_t i = 0; i < 2000000; i++) ;
		pinWrite(GPIOC, 13, HIGH);
		for (uint32_t i = 0; i < 2000000; i++) ;	  */
	}
}


void TIM2_IRQHandler()
{
	if (TIM2->SR & TIM_SR_UIF)
	{
		TIM2->SR &= ~TIM_SR_UIF; 
		
		if (counter > 40)
		{
			counter = 0;
		}
		/*
		DMA1_Channel5->CNDTR = 5;
		GPIOB->ODR &= ~(1 << 12);
		DMA1_Channel5->CCR |= DMA_CCR_EN;
		*/
		GPIOB->ODR &= ~(1 << 12);
		for (uint8_t i = 0; i < 40; i++)
		{
			GPIOB->ODR &= ~(1 << 13);
			pinWrite(GPIOB, 15, counter > i);
			GPIOB->ODR |= (1 << 13);
		}
		GPIOB->ODR |= (1 << 12);
		counter++;
		pinToggle(GPIOC, 13);
	}
}

void DMA1_Channel5_IRQHandler()
{
	DMA1_Channel5->CCR &= ~DMA_CCR_EN;
	GPIOB->ODR |= (1 << 12);
}
