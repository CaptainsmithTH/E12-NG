#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include <stm32f4xx.h>

#ifndef COMRETURNPARAMETER_INCLUDED
#define COMRETURNPARAMETER_INCLUDED

typedef struct 
{
	float currentSpeed;
	float currentKp;
	float currentKi;
	float currentKd;
	float resultedKp;
	float resultedKi;
	float resultedKd;
	float integralError;	
}returnPID_t;

typedef struct
{
	int64_t currentPosition;
	float currentSpeed;
}returnMeasured_t;

typedef struct
{
	uint16_t pwm;
	uint16_t dir;
}returnMotorPWM_t;

#endif