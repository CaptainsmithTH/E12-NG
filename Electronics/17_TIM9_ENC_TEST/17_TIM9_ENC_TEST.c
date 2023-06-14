#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>
#include "GPIO.h"
#include "CLOCK.h"

uint16_t TEST = 0;
uint32_t input[4000];

uint8_t nTime = 0;
uint8_t ccw = 0;
uint8_t cw = 0;
int64_t Mpos = 0;
uint8_t inConfig = 0;
uint64_t micros = 0;
uint64_t prevMicros = 0;
int64_t Mpos2 = 0;
void writeIn(uint8_t config)
{
	GPIOD->BSRR |= (1 << 16);
	for (uint8_t i = 0; i < 8; i++)
	{
		GPIOC->ODR &= ~(1 << 10);
		GPIOC->ODR |= ((config >> (7 - i)) & 1) << 12;
		GPIOC->ODR &= ((config >> (7 - i)) & 1) << 12 | ~(1 << 12);
		GPIOC->ODR |= (1 << 10);
	}
	GPIOD->BSRR |= (1 << 0);
}
uint64_t getMicros()
{
	return micros + TIM13->CNT;
}
uint64_t resultedMicros = 0;
uint8_t Test1 = 0, Test2 = 0;
void testMotor(uint8_t motorNumber, uint8_t dir, uint16_t pwm)
{
	if (motorNumber == 1)
	{
		TIM4->CCR3 = pwm;
		if (dir == 1)
		{
			inConfig |= (1 << 0);
			inConfig &= ~(1 << 1);
		}
		else if (dir == 2)
		{
			inConfig |= (1 << 1);
			inConfig &= ~(1 << 0);
		}
		else
		{
			inConfig &= ~(1 << 1 | 1 << 0);
		}
	}
	else if (motorNumber == 2)
	{
		
		TIM4->CCR4 = pwm;
		if (dir == 1)
		{
			inConfig |= (1 << 2);
			inConfig &= ~(1 << 3);
		}
		else if (dir == 2)
		{
			inConfig |= (1 << 3);
			inConfig &= ~(1 << 2);
		}
		else
		{
			inConfig &= ~(1 << 3 | 1 << 2);
		}
	}
	else if (motorNumber == 3)
	{
		TIM8->CCR4 = pwm;
		if (dir == 1)
		{
			inConfig |= (1 << 4);
			inConfig &= ~(1 << 5);
		}
		else if (dir == 2)
		{
			inConfig |= (1 << 5);
			inConfig &= ~(1 << 4);
		}
		else
		{
			inConfig &= ~(1 << 5 | 1 << 4);
		}
	}
	else if (motorNumber == 4)
	{
		TIM8->CCR3 = pwm;
		if (dir == 1)
		{
			inConfig |= (1 << 6);
			inConfig &= ~(1 << 7);
		}
		else if (dir == 2)
		{
			inConfig |= (1 << 7);
			inConfig &= ~(1 << 6);
		}
		else
		{
			inConfig &= ~(1 << 7 | 1 << 6);
		}
		
	}
	writeIn(inConfig);
}
int main(void)
{
	generalSetup();
	
	pinMode(GPIOB, 8, ALTFUNCTION);
	pinMode(GPIOB, 9, ALTFUNCTION);
	pinMode(GPIOC, 8, ALTFUNCTION);
	pinMode(GPIOC, 9, ALTFUNCTION);
	pinAlt(GPIOC, 9, 3);
	pinAlt(GPIOC, 8, 3);
	pinAlt(GPIOB, 8, 2);
	pinAlt(GPIOB, 9, 2);
	
	pinMode(GPIOC, 10, OUTPUT);
	pinMode(GPIOC, 12, OUTPUT);
	pinMode(GPIOD, 0, OUTPUT);
	GPIOD->BSRR |= (1 << 0);
	
	pinMode(GPIOA, 2, ALTFUNCTION);
	pinMode(GPIOA, 3, ALTFUNCTION);
	pinPull(GPIOA, 2, PULLUP);
	pinPull(GPIOA, 3, PULLUP);
	pinAlt(GPIOA, 2, 3);
	pinAlt(GPIOA, 3, 3);
	pinMode(GPIOE, 9, ALTFUNCTION);
	pinMode(GPIOE, 11, ALTFUNCTION);
	pinPull(GPIOE, 9, PULLUP);
	pinPull(GPIOE, 11, PULLUP);
	pinAlt(GPIOE, 9, 1);
	pinAlt(GPIOE, 11, 1);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->CR1 |= TIM_CR1_ARPE;
	TIM4->CR2 = 0;
	TIM4->SMCR = 0;
	TIM4->EGR = 0;
	TIM4->DIER = 0;
	TIM4->CNT = 0;
	TIM4->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	TIM4->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM4->PSC = 0;
	TIM4->ARR = 4200;
	TIM4->CCR3 = 2300;
	TIM4->CCR4 = 2300;
	TIM4->CR1 |= TIM_CR1_CEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
	TIM8->CR1 = 0;
	TIM8->CR1 |= TIM_CR1_ARPE;
	TIM8->CR2 = 0;
	TIM8->SMCR = 0;
	TIM8->EGR = 0;
	TIM8->DIER = 0;
	TIM8->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE | TIM_CCMR2_OC3PE;
	TIM8->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM8->BDTR |= TIM_BDTR_MOE;
	TIM8->PSC = 1;
	TIM8->ARR = 4200;
	TIM8->CCR3 = 2300;
	TIM8->CCR4 = 2300;
	TIM8->CR1  |= TIM_CR1_CEN;
	
	pinMode(GPIOA, 0, ALTFUNCTION);
	pinMode(GPIOA, 1, ALTFUNCTION);
	pinMode(GPIOA, 2, ALTFUNCTION);
	pinMode(GPIOA, 3, INPUT);
	pinMode(GPIOA, 6, ALTFUNCTION);
	pinMode(GPIOA, 7, ALTFUNCTION);
	pinMode(GPIOE, 9, ALTFUNCTION);
	pinMode(GPIOE, 11, ALTFUNCTION);
	pinAlt(GPIOA, 0, 1);
	pinAlt(GPIOA, 1, 1);
	pinAlt(GPIOA, 2, 3);
	pinAlt(GPIOA, 6, 2);
	pinAlt(GPIOA, 7, 2);
	pinAlt(GPIOE, 9, 1);
	pinAlt(GPIOE, 11, 1);
	pinPull(GPIOA, 0, PULLUP);
	pinPull(GPIOA, 1, PULLUP);
	pinPull(GPIOA, 2, PULLUP);
	pinPull(GPIOA, 3, PULLUP);
	pinPull(GPIOA, 6, PULLUP);
	pinPull(GPIOA, 7, PULLDOWN);
	pinPull(GPIOE, 9, PULLUP);
	pinPull(GPIOE, 11, PULLUP);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CR2 = 0;
	TIM2->CR1 = 0;
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC2F_2;  
	TIM2->DIER = 0;
	TIM2->CCER = 0;
	TIM2->SMCR = 0;
	TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	TIM2->CNT = 32767;
	TIM2->CR1 |= TIM_CR1_CEN;
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
	TIM9->CR2 = 0;
	TIM9->CR1 = 0;
	TIM9->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM9->CCER = 0;
	TIM9->DIER = 0;
	TIM9->SMCR = 0;
	TIM9->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_2 | TIM_SMCR_TS_0 | TIM_SMCR_TS_2;
	TIM9->CNT = 32767;
	TIM9->CR1 |= TIM_CR1_CEN;	
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1->CR2 = 0;
	TIM1->CR1 = 0;
	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC2F_2;
	TIM1->CCER = 0;
	TIM1->SMCR = 0;
	TIM1->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	TIM1->CNT = 32767;
	TIM1->CR1 |= TIM_CR1_CEN;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->CR2 = 0;
	TIM3->CR1 = 0;
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC2F_2;
	TIM3->CCER = 0;
	TIM3->SMCR = 0;
	TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	TIM3->CNT = 32767;
	TIM3->CR1 |= TIM_CR1_CEN;
	
	writeIn(0b10101010);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	TIM7->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
	TIM7->CR2 = 0;
	TIM7->DIER |= TIM_DIER_UIE;
	TIM7->CNT = 0;
	TIM7->PSC = 83;
	TIM7->ARR = 2000;
	TIM7->CR1 |= TIM_CR1_CEN;
	attachInterrupt(GPIOA,2,RISING);
	NVIC_EnableIRQ(TIM7_IRQn);
	//NVIC_EnableIRQ(EXTI2_IRQn);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM13EN;
	TIM13->CR1 = 0;
	TIM13->CR2 = 0;
	TIM13->CR1 |= TIM_CR1_ARPE;
	TIM13->DIER = 0;
	TIM13->SMCR = 0;
	TIM13->DIER |= TIM_DIER_UIE;
	TIM13->CNT = 0;
	TIM13->PSC = 83;
	TIM13->ARR = 65535;
	TIM13->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn);
	
	
	for (;;)
	{
		TEST = TIM3->CNT;
		Test1 = pinRead(GPIOA, 6);
		Test2 = pinRead(GPIOA, 7);
	}
}
void TIM8_UP_TIM13_IRQHandler()
{
	if (TIM13->SR & TIM_SR_UIF)
	{
		TIM13->SR &= ~TIM_SR_UIF;
		micros += 65536;
	}
}

void TIM7_IRQHandler()
{
	if (TIM7->SR & TIM_SR_UIF)
	{
		TIM7->SR &= ~TIM_SR_UIF;
		//DMA2_Stream1->PAR = (uint32_t)&GPIOA->IDR;
		//DMA2_Stream1->M0AR = (uint32_t)input;
		//DMA2_Stream1->NDTR = 10;
		//DMA2_Stream1->CR |= DMA_SxCR_EN;
		Mpos2 += (int16_t)(TIM2->CNT - 32767);
		TIM2->CNT = 32767;
		prevMicros = getMicros();
		//EXTI->IMR |= (1 << 2);
		
	}
}

void EXTI2_IRQHandler()
{
	
	if (GPIOA->IDR & (1 << 3))
	{
		Mpos += (int64_t)TIM9->CNT - 32767;
	}
	else
	{
		Mpos -= (int64_t)TIM9->CNT - 32767;
	}
	TIM9->CNT = 32767;
	resultedMicros = getMicros() -prevMicros;
	EXTI->IMR &= ~(1 << 2);
	EXTI->PR |= (1 << 2);
}

void DMA2_Stream1_IRQHandler()
{
	if (DMA2->LISR & DMA_LISR_TCIF1)
	{
		DMA2->LIFCR |= DMA_LIFCR_CTCIF1;
		DMA2_Stream1->CR &= ~DMA_SxCR_EN;
	}
}
