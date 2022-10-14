#include "source/E12_STM32_Rx.h"

uint8_t packet[32];

uint8_t rev_packet[32];

int main(void)
{
	for (uint8_t i = 0; i < 32; i++)
	{
		packet[i] = i + 0x40;
		rev_packet[i] = 0;
	}
	general_Setup();
	pinMode(GPIOC, 13, OUTPUT50, PUSHPULL);
	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	pinMode(GPIOB, 12, OUTPUT50, PUSHPULL);
	pinMode(GPIOB, 13, OUTPUT50, ALTPUSHPULL);
	pinMode(GPIOB, 14, INPUT, FLOATING);
	pinMode(GPIOB, 15, OUTPUT50, ALTPUSHPULL);
	
	SPI2->CR1 |= SPI_CR1_MSTR | SPI_CR1_BR_0;
	SPI2->CR2 |= SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN | SPI_CR2_SSOE;
	
	DMA1_Channel5->CNDTR = 32;
	DMA1_Channel5->CPAR = (uint32_t)&SPI2->DR;
	DMA1_Channel5->CMAR = (uint32_t)packet;
	DMA1_Channel5->CCR |= DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_MINC | DMA_CCR_TCIE;
	DMA1_Channel4->CNDTR = 32;
	DMA1_Channel4->CPAR = (uint32_t)&SPI2->DR;
	DMA1_Channel4->CMAR = (uint32_t)rev_packet;
	DMA1_Channel4->CCR |= DMA_CCR_CIRC | DMA_CCR_MINC | DMA_CCR_TCIE;
	DMA1_Channel4->CCR |= DMA_CCR_EN;
	
	NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);
	
	SPI2->CR1 |= SPI_CR1_SPE;
	
	while (true) 
	{
		pinToggle(GPIOC, 13);
		GPIOB->ODR &= ~(1 << 12);
		DMA1_Channel5->CNDTR = 32;
		DMA1_Channel5->CCR |= DMA_CCR_EN;
		DMA1_Channel4->CNDTR = 32;
		DMA1_Channel4->CCR |= DMA_CCR_EN;
		for (uint32_t i = 0; i < 500000; i++) ;
	}
	
	
	
}

void DMA1_Channel5_IRQHandler()
{
	if (DMA1->ISR & DMA_ISR_TCIF5)
	{
		DMA1->IFCR |= DMA_IFCR_CTCIF5;
		DMA1_Channel5->CCR &= ~DMA_CCR_EN;
		for (uint8_t i = 0; i < 120; i++) ;
		GPIOB->ODR |= (1 << 12);
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