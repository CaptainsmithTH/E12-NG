#include "dcMotor.h"

void dcMotorPIDInit(dcMotor* motor)
{
	PIDInit(&(motor->speedPID));
	PIDInit(&(motor->positionPID));
}

void dcMotorKineticParametersInit(dcMotor* motor)
{
	motor->kinetic.currentPosition = 0;
	motor->kinetic.prevPosition = 0;
	motor->kinetic.prevMicros = 0;
	motor->kinetic.currentSpeed = 0;
}
void messageAssemble(uint8_t* message, dcMotor* motor)
{
	*(uint16_t *)(message + cmdOffset) = (*(dcMotor *)(motor)).cmd;
	*(uint32_t *)(message + statusOffset) = (*(dcMotor *)(motor)).status;
}

void convertPIDToPWM(dcMotor* motor)
{
	if (motor->speedPID.resultedPID > 4200)
	{
		motor->pwm = 4200;
		motor->dir = 0b01;
	}
	else if (motor->speedPID.resultedPID > 0)
	{
		motor->pwm = (uint16_t)motor->speedPID.resultedPID;
		motor->dir = 0b01;
	}
	else if (motor->speedPID.resultedPID >= 4200)
	{
		motor->pwm = (uint16_t)(-(motor->speedPID.resultedPID));
		motor->dir = 0b10;
	}
	else
	{
		motor->pwm = 4200;
		motor->dir = 0b10;
	}
}


