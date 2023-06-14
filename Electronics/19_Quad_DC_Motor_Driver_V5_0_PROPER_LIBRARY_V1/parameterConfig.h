#ifndef MOTORPARAMETER_INCLUDED
#define MOTORPARAMETER_INCLUDED
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include <stm32f4xx.h>
#include "comReturnParameter.h"
#include "pid.h"

typedef struct
{
	float speedKp;
	float speedKi;
	float speedKd;
	float positionKp;   
	float positionKi;
	float positionKd;
	float maxSpeed;
	uint32_t encPPR;
}motorParameter_t;

#endif