#ifndef MOTORCONTROL_INCLUDED
#define MOTORCONTROL_INCLUDED
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include <stm32f4xx.h>
#include "GPIO.h"
#include "dcMotor.h"

static uint8_t inConfig = 0;

static uint32_t* motorChannel[4] = {
	(uint32_t *)&TIM4->CCR3,
	(uint32_t *)&TIM4->CCR4,
	(uint32_t *)&TIM8->CCR4,
	(uint32_t *)&TIM8->CCR3
};
void motorSetup();

void driveInConfig(uint8_t inConfig);

void driveMotor(dcMotor* M);
#endif