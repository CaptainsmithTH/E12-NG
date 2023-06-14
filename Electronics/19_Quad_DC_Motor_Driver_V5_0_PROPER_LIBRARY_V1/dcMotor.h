
#ifndef DCMOTOR_INCLUDED
#define DCMOTOR_INCLUDED	
#include "parameterConfig.h"
#include "positionControl.h"
#include "speedControl.h"
#include "pwmControl.h"
#include "pid.h"

#define cmdOffset 118
#define statusOffset 120
typedef struct
{
	speedControl_t speedControl;
	positionControl_t positionControl;
	pwmControl_t pwmControl;
}packet_t;

typedef struct
{
	int64_t currentPosition;
	int64_t prevPosition;
	uint64_t prevMicros;
	float currentSpeed;
	float interval;
}kineticParameters;

typedef struct
{
	packet_t packet;
	PID_t speedPID;
	PID_t positionPID;
	kineticParameters kinetic;
	uint16_t mode;
	uint16_t cmd;
	uint32_t status;
	uint16_t pwm;
	uint16_t dir;
}dcMotor;

void dcMotorPIDInit(dcMotor* motor);
void dcMotorKineticParametersInit(dcMotor* motor);
void convertPIDToPWM(dcMotor* motor);
void txMessageAssemble(uint8_t* message, dcMotor* motor);


#endif

