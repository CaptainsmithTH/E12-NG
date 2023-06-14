#include "SETUP.h"
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
void E12BusSetup()
{
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
	DMA2_Stream3->CR = 0;
	DMA2_Stream3->FCR = 0;
	DMA2_Stream3->CR |= DMA_SxCR_TCIE | DMA_SxCR_MINC | DMA_SxCR_DIR_0 | 3 << DMA_SxCR_CHSEL_Pos;
	SPI1->CR1 |= SPI_CR1_CRCEN;
	SPI1->CR2 |= SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN;
	SPI1->CR1 |= SPI_CR1_SPE;
	
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	NVIC_SetPriority(DMA2_Stream3_IRQn, 0);
	NVIC_SetPriority(DMA2_Stream0_IRQn, 0);
	NVIC_SetPriority(TIM8_TRG_COM_TIM14_IRQn, 4);
}
void encoderSetup()
{
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
	pinAlt(GPIOA, 3, 3);
	pinAlt(GPIOA, 6, 2);
	pinAlt(GPIOA, 7, 2);
	pinAlt(GPIOE, 9, 1);
	pinAlt(GPIOE, 11, 1);
	pinPull(GPIOA, 0, PULLUP);
	pinPull(GPIOA, 1, PULLUP);
	pinPull(GPIOA, 2, PULLUP);
	pinPull(GPIOA, 3, PULLUP);
	pinPull(GPIOA, 6, PULLUP);
	pinPull(GPIOA, 7, PULLUP);
	pinPull(GPIOE, 9, PULLUP);
	pinPull(GPIOE, 11, PULLUP);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CR2 = 0;
	TIM2->CR1 = 0;
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC2F_2;
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
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	TIM7->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
	TIM7->CR2 = 0;
	TIM7->DIER |= TIM_DIER_UIE;
	TIM7->CNT = 0;
	TIM7->PSC = 83;
	TIM7->ARR = 2000;
	TIM7->CR1 |= TIM_CR1_CEN;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;
	TIM12->CR1 = 0;
	TIM12->CR2 = 0;
	TIM12->CR1 |= TIM_CR1_ARPE;
	TIM12->DIER = 0;
	TIM12->DIER |= TIM_DIER_UIE;
	TIM12->CNT = 0;
	TIM12->PSC = 83;
	TIM12->ARR = 10;
	TIM12->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);
	NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 1);
	NVIC_SetPriority(EXTI2_IRQn, 1);
	
	attachInterrupt(GPIOA, 2, RISING);
	NVIC_EnableIRQ(TIM7_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
}
void indicatorSetup()
{
	pinMode(GPIOD, 2, OUTPUT);
	GPIOD->BSRR |= (1 << 2);
	pinMode(GPIOD, 3, OUTPUT);
	GPIOD->BSRR |= (1 << 3);
	pinMode(GPIOD, 3, OUTPUT);
	GPIOD->BSRR |= (1 << 4);
	
	pinMode(GPIOD, 14, OUTPUT);
	pinMode(GPIOD, 15, OUTPUT);
	GPIOD->ODR |= (1 << 14 | 1 << 15);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
	TIM6->CR2 = 0;
	TIM6->DIER |= TIM_DIER_UIE;
	TIM6->CNT = 0;
	TIM6->PSC = 41999;
	TIM6->ARR = 2000;
	TIM6->CR1 |= TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}
void EXTI15_10_IRQHandler()
{
	SPI1->CR1 &= ~SPI_CR1_CRCEN;
	SPI1->CR1 |= SPI_CR1_CRCEN;
	SPI1->CRCPR = 0xB7;
	
	
	DMA2_Stream0->CR &= ~DMA_SxCR_EN;
	DMA2->LIFCR |= DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0;
	DMA2_Stream0->CR |= DMA_SxCR_MINC | DMA_SxCR_TCIE;
	DMA2_Stream0->NDTR = packetSize;
	DMA2_Stream0->PAR = (uint32_t)&SPI1->DR;
	DMA2_Stream0->M0AR = (uint32_t)RXPacket;
	DMA2_Stream0->CR |= DMA_SxCR_EN;
	
	DMA2_Stream3->CR &= ~DMA_SxCR_EN;
	DMA2->LIFCR |= DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3;
	DMA2_Stream3->NDTR = packetSize;
	DMA2_Stream3->PAR = (uint32_t)&SPI1->DR;
	DMA2_Stream3->M0AR = (uint32_t)TXPacket;
	DMA2_Stream3->CR |= DMA_SxCR_EN;
	
	clearInterrupt(GPIOA, 15);
	counter[1]++;
	connectedCounter = 0;
	
}
void DMA2_Stream0_IRQHandler()
{
	counter[2]++;
	if (DMA2->LISR & DMA_LISR_TCIF0)
	{
		DMA2->LIFCR |= DMA_LIFCR_CTCIF0 | DMA_LIFCR_CHTIF0;
		DMA2_Stream0->CR &= ~DMA_SxCR_EN;
		calculatedCRC = SPI1->RXCRCR;
		SPI1->CR1 &= ~SPI_CR1_CRCEN;
		DMA2_Stream0->CR &= ~(DMA_SxCR_MINC | DMA_SxCR_TCIE);
		DMA2_Stream0->M0AR = (uint32_t)&trash;
		DMA2_Stream0->PAR = (uint32_t)&SPI1->DR;
		DMA2_Stream0->NDTR = 65535;			
		DMA2_Stream0->CR |= DMA_SxCR_EN;
		if (RXPacketProcess(RXPacket,M) == 0)
		{
			timeOutCounter = 0;
		}
		TXPacketProcess(TXPacket, M);
	}
}
void TIM7_IRQHandler()
{
	if (TIM7->SR & TIM_SR_UIF)
	{
		TIM7->SR &= ~TIM_SR_UIF;  
		buffer = TIM2->CNT;
		TIM2->CNT = 32767;
		M[0].currentPos += (int16_t)(buffer - 32767) ;
		buffer = TIM3->CNT;
		TIM3->CNT = 32767;
		M[2].currentPos += (int16_t)(buffer - 32767) ;
		buffer = TIM1->CNT;
		TIM1->CNT = 32767;
		M[3].currentPos += (int16_t)(buffer - 32767);
		
	}
}
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
void TIM6_DAC_IRQHandler()
{
	if (TIM6->SR & TIM_SR_UIF)
	{
		TIM6->SR &= ~TIM_SR_UIF;
		state = !state;
		if (state)
		{
			GPIOD->BSRR |= (1 << 2);
			
		}
		else
		{
			
			GPIOD->BSRR |= (1 << 18);
		}
	}
}
void DMA2_Stream3_IRQHandler()
{
	if (DMA2->LISR & DMA_LISR_TCIF3)
	{
		DMA2->LIFCR |= DMA_LIFCR_CTCIF3;
		DMA2_Stream3->CR &= ~DMA_SxCR_EN;
		counter[3]++;
	}
}
void microsSetup()
{
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
}
void TIM8_UP_TIM13_IRQHandler()
{
	if (TIM13->SR & TIM_SR_UIF)
	{
		TIM13->SR &= ~TIM_SR_UIF;
		micros += 65536;
	}
}
void EXTI2_IRQHandler()
{
	
	if (GPIOA->IDR & (1 << 3))
	{
		buffer = TIM9->CNT;
		TIM9->CNT = 32767;
		M[1].currentPos -= (int64_t)(buffer - 32767)*4;
	}
	else
	{	
		buffer = TIM9->CNT;
		TIM9->CNT = 32767;
		M[1].currentPos += (int64_t)(buffer - 32767) * 4;
	}
	EXTI->IMR &= ~(1 << 2);
	EXTI->PR |= (1 << 2);
}

void TIM8_BRK_TIM12_IRQHandler()
{
	if (TIM12->SR & TIM_SR_UIF)
	{
		TIM12->SR &= ~TIM_SR_UIF;
		EXTI->IMR |= (1 << 2);
	}
}