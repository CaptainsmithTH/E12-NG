#include "source/E12_STM32_Rx.h"
uint8_t prev_packet[32];
uint8_t new_packet[32];

int main(void)
{
	for (uint8_t i = 0; i < 32; i++)
	{
		prev_packet[i] = 0x00;
		new_packet[i] =  0x00;
	}
	general_Setup();
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	pinMode(GPIOB, 12, INPUT, PULLUP);
	pinMode(GPIOB, 13, INPUT, FLOATING);
	pinMode(GPIOB, 14, OUTPUT50, ALTPUSHPULL);
	pinMode(GPIOB, 15, INPUT, FLOATING);
	
	SPI2->CR2 |= SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN;
	
	attachInterrupt(GPIOB, 12, FALLING);
	
	DMA1_Channel4->CNDTR = 32;
	DMA1_Channel4->CMAR = (uint32_t)prev_packet;
	DMA1_Channel4->CPAR = (uint32_t)&SPI2->DR;
	DMA1_Channel4->CCR |= DMA_CCR_CIRC | DMA_CCR_MINC | DMA_CCR_TCIE;
	DMA1_Channel5->CNDTR = 32;
	DMA1_Channel5->CMAR = (uint32_t)new_packet;
	DMA1_Channel5->CPAR = (uint32_t)&SPI2->DR;
	DMA1_Channel5->CCR |= DMA_CCR_CIRC | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE;
	DMA1_Channel5->CCR |= DMA_CCR_EN;
	NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	SPI2->CR1 |= SPI_CR1_SPE;
	
	while (true)
	{
		
		
	}
}

void DMA1_Channel4_IRQHandler()
{
	if (DMA1->ISR & DMA_ISR_TCIF4)
	{
		DMA1->IFCR |= DMA_IFCR_CTCIF4;
		DMA1_Channel4->CCR &= ~DMA_CCR_EN;
	}
}

void DMA1_Channel5_IRQHandler()
{
	if (DMA1->ISR & DMA_ISR_TCIF5)
	{
		DMA1->IFCR |= DMA_IFCR_CTCIF5;
		DMA1_Channel5->CCR &= ~DMA_CCR_EN;
		DMA1_Channel5->CCR |= DMA_CCR_EN;
	}
}

void EXTI15_10_IRQHandler()
{
	DMA1_Channel4->CCR |= DMA_CCR_EN;
	for (uint8_t i = 0; i < 32; i++)
	{
		new_packet[i] = prev_packet[i] + 0x0F;
	}
	
	resetInterrupt(GPIOB, 12);
}