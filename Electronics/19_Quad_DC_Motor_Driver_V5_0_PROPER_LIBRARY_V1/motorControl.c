#include "motorControl.h"
void motorSetup()
{
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
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
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
	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;
	TIM4->CR1 |= TIM_CR1_CEN;
	
	TIM8->CR1 = 0;
	TIM8->CR1 |= TIM_CR1_ARPE;
	TIM8->BDTR |= TIM_BDTR_MOE;
	TIM8->CR2 = 0;
	TIM8->SMCR = 0;
	TIM8->EGR = 0;
	TIM8->DIER = 0;
	TIM8->CNT = 0;
	TIM8->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	TIM8->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;
	TIM8->PSC = 1;
	TIM8->ARR = 4200;
	TIM8->CCR3 = 0;
	TIM8->CCR4 = 0;
	TIM8->CR1 |= TIM_CR1_CEN;
}

void driveMotor(dcMotor* M)
{
	inConfig = 0;
	for (uint8_t i = 0; i < 4; i++)
	{
		inConfig |= M[i].dir << 2*i;
		*(motorChannel[i]) = M[i].pwm;
	}
	driveInConfig(inConfig);
}

void driveInConfig(uint8_t inConfig)
{
	GPIOD->BSRR |= (1 << 16);
	for (uint8_t i = 0; i < 8; i++)
	{
		GPIOC->ODR &= ~(1 << 10);
		GPIOC->ODR |= ((inConfig >> (7 - i)) & 1) << 12;
		GPIOC->ODR &= ((inConfig >> (7 - i)) & 1) << 12 | ~(1 << 12);
		GPIOC->ODR |= (1 << 10);
	}
	GPIOD->BSRR |= (1 << 0);
}