#include "source/E12_STM32_Rx.h"

uint8_t sendPacket[32];
uint8_t recvPacket[32];

int main(void)
{
	general_Setup();
	
	for (uint8_t i = 0; i < 32; i++)
	{
		sendPacket[i] = 0x40 + i;
	}
	
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	pinMode(GPIOB, 10, OUTPUT50, ALTPUSHPULL);
	pinMode(GPIOB, 11, INPUT, FLOATING);
	
	DMA1_Channel2->CPAR = (uint32_t)&USART3->DR;
	DMA1_Channel2->CNDTR = 32;
	DMA1_Channel2->CMAR = (uint32_t)sendPacket;
	DMA1_Channel2->CCR |= DMA_CCR_CIRC | DMA_CCR_DIR | DMA_CCR_TCIE | DMA_CCR_MINC;
	
	DMA1_Channel3->CPAR = (uint32_t)&USART3->DR;
	DMA1_Channel3->CMAR = (uint32_t)recvPacket;
	DMA1_Channel3->CNDTR =  32;
	DMA1_Channel3->CCR |= DMA_CCR_CIRC | DMA_CCR_MINC | DMA_CCR_TCIE;
	
	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);
	
	USART3->BRR = 1<<4;
	USART3->CR3 |= USART_CR3_DMAR | USART_CR3_DMAT;
	USART3->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	DMA1_Channel3->CCR |= DMA_CCR_EN;
	
	pinMode(GPIOC, 13, OUTPUT50, PUSHPULL);
	
	while (true)
	{
		
		DMA1_Channel2->CCR |= DMA_CCR_EN;
		for (uint32_t i = 0; i < 500000; i++) ;
		pinToggle(GPIOC, 13);
		
	}
}

void DMA1_Channel2_IRQHandler()
{
	if (DMA1->ISR & DMA_ISR_TCIF2)
	{
		DMA1->IFCR |= DMA_IFCR_CTCIF2;
		DMA1_Channel2->CCR &= ~DMA_CCR_EN;
		
		
	}
}

void DMA1_Channel3_IRQHandler()
{
	if (DMA1->ISR & DMA_ISR_TCIF3)
	{
		DMA1->IFCR |= DMA_IFCR_CTCIF3;
		DMA1_Channel3->CCR &= ~DMA_CCR_EN;
		DMA1_Channel3->CCR |= DMA_CCR_EN;
	}
}