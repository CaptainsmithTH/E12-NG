#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>
#include "GPIO.h"
#include "CLOCK.h"
#include "SETUP.h"

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
	cycleSetup();
	PID_Initialization();
	
	for (;;)
	{
		
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
			processMotor(&M[i]);
			driveMotor(&M[i]);
		}
		timeOutCounter++;
		connectedCounter++;
		if (timeOutCounter > 10)
		{	
			GPIOD->ODR &= ~(1 << 14);
		}
		else
		{			
			GPIOD->ODR |= (1 << 14);
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