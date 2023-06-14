#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>
#include "GPIO.h"
#include "CLOCK.h"
uint8_t packet[1024];
uint8_t counter = 0;
uint8_t indicator1 = 0;

uint8_t indicator2 = 0;

uint16_t resultedCRC = 0;

uint8_t buffer;

uint8_t state = 0;
int64_t encoderCounter = 0;
uint64_t counter1 = 0;
uint64_t counter2 = 0;
uint64_t counter3 = 0;

uint32_t temp = 0;

void writeIn(uint8_t config)
{
	GPIOD->BSRR |= (1 << 16);
	for (uint8_t i = 0; i < 8; i++)
	{
		GPIOC->ODR &= ~(1 << 10);
		GPIOC->ODR |= ((config >> (7 - i)) & 1) << 12;
		GPIOC->ODR &= ((config >> (7 - i)) & 1) << 12 | ~(1<<12);
		GPIOC->ODR |= (1 << 10);
	}
	GPIOD->BSRR |= (1 << 0);
}

int main(void)
{
	
	generalSetup();
										/*
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	TIM4->CR1 |= TIM_CR1_ARPE;
	TIM4->CR2 = 0;
	TIM4->SMCR = 0;
	TIM4->EGR = 0;
	TIM4->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC4PE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
	TIM4->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM4->PSC = 83;
	TIM4->ARR = 1000;
	TIM4->CCR3 = 500;
	TIM4->CCR4 = 750;
	TIM4->CR1 |= TIM_CR1_CEN;
	
	TIM8->CR1 |= TIM_CR1_ARPE;
	TIM8->BDTR |= TIM_BDTR_MOE;
	TIM8->CR2 = 0;
	TIM8->SMCR = 0;
	TIM8->EGR = 0;
	TIM8->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC4PE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
	TIM8->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM8->PSC = 167;
	TIM8->ARR = 1000;
	TIM8->CCR3 = 500;
	TIM8->CCR4 = 750;
	TIM8->CR1 |= TIM_CR1_CEN;		*/

	//Warning: if the line below triggers an error, GPIOC is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOC' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	pinMode(GPIOD, 2, OUTPUT);
	pinMode(GPIOD, 3, OUTPUT);
	GPIOD->BSRR |= (1 << 3);
	
	pinMode(GPIOD, 14, OUTPUT);
	pinMode(GPIOD, 15, OUTPUT);
	GPIOD->ODR |= (1 << 14 | 1 << 15);
	
	pinMode(GPIOC, 8, ALTFUNCTION);
	pinMode(GPIOC, 9, ALTFUNCTION);
	pinMode(GPIOB, 8, ALTFUNCTION);
	pinMode(GPIOB, 9, ALTFUNCTION);
	pinAlt(GPIOC, 9, 3);
	pinAlt(GPIOC, 8, 3);
	pinAlt(GPIOB, 8, 2);
	pinAlt(GPIOB, 9, 2);
	
	pinMode(GPIOC, 10, OUTPUT);
	pinMode(GPIOC, 12, OUTPUT);
	pinMode(GPIOD, 0, OUTPUT);
	GPIOD->BSRR |= (1 << 0);
	
	pinMode(GPIOA, 0, ALTFUNCTION);
	pinMode(GPIOA, 1, ALTFUNCTION);
	pinPull(GPIOA, 1, PULLUP);
	pinPull(GPIOA, 0, PULLUP);
	pinAlt(GPIOA, 0, 1);
	pinAlt(GPIOA, 1, 1);
	
	pinMode(GPIOB, 3, ALTFUNCTION);
	pinMode(GPIOB, 4, ALTFUNCTION);
	pinMode(GPIOB, 5, ALTFUNCTION);
	pinAlt(GPIOB, 3, 5);
	pinAlt(GPIOB, 4, 5);
	pinAlt(GPIOB, 5, 5);
	pinMode(GPIOA, 15, ALTFUNCTION);
	pinPull(GPIOA, 15, PULLUP);
	pinAlt(GPIOA, 15, 5);
	attachInterrupt(GPIOA, 15, FALLING);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	DMA2_Stream0->CR = 0;
	DMA2_Stream0->FCR = 0;
	DMA2_Stream0->CR |= DMA_SxCR_TCIE | DMA_SxCR_MINC | 3 << DMA_SxCR_CHSEL_Pos;
	SPI1->CR1 |= SPI_CR1_CRCEN;
	SPI1->CR2 |= SPI_CR2_RXDMAEN;
	SPI1->CR1 |= SPI_CR1_SPE;
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
	TIM6->CR2 = 0;
	TIM6->DIER |= TIM_DIER_UIE;
	TIM6->CNT = 0;
	TIM6->PSC = 41999;
	TIM6->ARR = 2000;
	TIM6->CR1 |= TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
	for (;;)
	{
		
	}
}

void EXTI15_10_IRQHandler()
{
	SPI1->CR1 &= ~SPI_CR1_CRCEN;
	SPI1->CR1 |= SPI_CR1_CRCEN;
	SPI1->CRCPR = 0xB7;
	DMA2_Stream0->NDTR = 117;
	DMA2_Stream0->PAR = (uint32_t)&SPI1->DR;
	DMA2_Stream0->M0AR = (uint32_t)packet;
	DMA2_Stream0->CR |= DMA_SxCR_EN;
	clearInterrupt(GPIOA, 15);
	counter1++;
}

void DMA2_Stream0_IRQHandler()
{
	temp = DMA2->LISR;
	if (DMA2->LISR & DMA_LISR_TCIF0)
	{
		DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
		DMA2_Stream0->CR &= ~DMA_SxCR_EN;
		while (!(SPI1->SR & SPI_SR_RXNE)) ;
		buffer = SPI1->DR;
		counter2++;
		
	}
	GPIOD->BSRR |= (1 << 3);
}

void TIM6_DAC_IRQHandler()
{
	if (TIM6->SR & TIM_SR_UIF)
	{
		TIM6->SR &= ~TIM_SR_UIF;
		state = !state;
		if (state)
		{
			GPIOD->BSRR |= (1 << 2);
			writeIn(0b00001010);
			TIM4->CCR3 = 500;
			TIM4->CCR4 = 1000;
			GPIOD->ODR &= ~(1 << 14);
			GPIOD->ODR |= (1 << 15);
			
		}
		else
		{
			
			GPIOD->BSRR |= (1 << 18);
			writeIn(0b00000101);
			TIM4->CCR3 = 1000;
			TIM4->CCR4 = 500;
			GPIOD->ODR &= ~(1 << 15);
			GPIOD->ODR |= (1 << 14);
		}
	}
}
