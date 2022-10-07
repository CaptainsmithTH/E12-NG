#include "CLOCK.h"
#include "GPIO.h"
#include "REMAP.h"

void E12Setup()
{
	remap_SPI1();
	general_Setup();
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
}