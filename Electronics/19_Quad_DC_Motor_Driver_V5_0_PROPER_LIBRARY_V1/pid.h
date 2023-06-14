#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "stm32f4xx.h"
#include "CLOCK.h"

#ifndef PID_INCLUDED
#define PID_INCLUDED
typedef struct
{
	uint64_t prevMicros;
	float kp;
	float ki;
	float kd;
	float targeted;
	float current;
	float interval;
	float error;
	float prevError;
	float integralError;
	float derivativeError;
	float resultedP;
	float resultedI;
	float resultedD;
	float resultedPID;
}PID_t;
void PIDCalculator(PID_t* controller);
void PIDInit(PID_t* controller);
#endif
