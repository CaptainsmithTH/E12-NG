#include "SETUP.h"


void E12_ComSetup(uint32_t address)
{
	remap_SPI1();
	general_Setup();
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	SPI1->CR1 |= SPI_CR1_CRCEN;
}

void E12_SPI2Setup(uint32_t address)
{
	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	
}