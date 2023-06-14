#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>
#include "GPIO.h"
#include "CLOCK.h"
#include "PID.h"

uint64_t prevDirectionChangeTime[4] = { 0, 0, 0, 0 };
uint8_t prevDir[4] = { 0, 0, 0, 0 };
#define minimumDirectionChangeTime 80000 //us

uint8_t RXPacket[1024];
uint8_t TXPacket[1024];
double MSpeed[4] = { 0, 0, 0, 0 };
uint8_t inConfig = 0;
uint8_t direction[4] = { 0, 0, 0, 0 };
uint32_t status = 0;
uint8_t trash;

int16_t PWM[4] = { 0, 0, 0, 0 };
motor M[4];
uint8_t state;
uint64_t counter[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float generalMonitor[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t indicator1 = 0;
uint64_t counter3 = 0;
uint64_t counter1 = 0;
uint64_t counter2 = 0;
uint64_t timeOutCounter = 0;
uint64_t connectedCounter = 0;
uint32_t test = 0;
uint8_t calculatedCRC = 0;
uint8_t receivedCRC = 0;
uint64_t prevMicros = 0;
uint64_t micros = 0;
uint64_t counter4 = 0;
float timeConstantTest = 0;
motorPID_t defaultMotorPID = { 0, 0, 0, 0, 0, 0, 0, 0 };
uint16_t buffer = 0;
uint32_t temp = 0;



int main(void)
{
	generalSetup();
	motorSetup();
	E12BusSetup();
	indicatorSetup();
	encoderSetup();
	microsSetup();
	for (uint8_t i = 0; i < 4; i++)
	{
		M[i].speedPID = defaultMotorPID;
		M[i].posPID = defaultMotorPID;
		M[i].speedPID.errorIntegral = 0;
		M[i].posPID.errorIntegral = 0;
		M[i].parameter.encCPR = 1024;
		M[i].prevMicros = 0;
		M[i].prevDir = 0;
		PIDInit(&M[i]);
	}
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	TIM14->CR1 = 0;
	TIM14->CR2 = 0;
	TIM14->CR1 |= TIM_CR1_ARPE;
	TIM14->DIER = 0;
	TIM14->SMCR = 0;
	TIM14->DIER |= TIM_DIER_UIE;
	TIM14->CNT = 0;
	TIM14->PSC = 83;
	TIM14->ARR = 2000;
	TIM14->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
	
	
	
	
	
	for (;;)
	{
		counter[5] = TIM1->CNT;	
	}
}

void TIM8_TRG_COM_TIM14_IRQHandler()
{
	
	if (TIM14->SR & TIM_SR_UIF)
	{
		TIM14->SR &= ~TIM_SR_UIF;
		counter[0]++;
		for (uint8_t i = 0; i < 4; i++)
		{
			if (M[i].mode == speedControlCMD)
			{
				getSpeedPID(&M[i]);
			}
			else if (M[i].mode == positionControlCMD)
			{
				getPosPID(&M[i]);
			}
			else if (M[i].mode == directControlCMD)
			{
				
			}
			else
			{
				M[i].pwm = 0;
				M[i].dir = 0;
			}
		}
		
		TIM4->CCR3 = M[0].pwm;
		TIM4->CCR4 = M[1].pwm;
		TIM8->CCR4 = M[2].pwm;
		TIM8->CCR3 = M[3].pwm;
		inConfig = 0;
		for (uint8_t i = 0; i < 4; i++)
		{
			inConfig |= M[i].dir << (i * 2);
		}
		
		writeIn(inConfig);
		timeOutCounter++;
		connectedCounter++;
		
		if (timeOutCounter > 10)
		{	
			GPIOD->ODR &= ~(1 << 14);
		}
		else
		{			
			GPIOD->ODR |= (1<<14);
		}
		if (connectedCounter > 10)
		{	
			GPIOD->ODR |= (1 << 15);
		}
		else
		{			
			GPIOD->ODR &= ~(1 << 15);
		}
	}
}