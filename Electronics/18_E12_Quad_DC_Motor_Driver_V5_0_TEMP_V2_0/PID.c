#include "PID.h"
#include <stdlib.h>
#include <stdio.h>
uint64_t getMicros()
{
	return micros + TIM13->CNT;
}
void PIDInit(motor* M)
{
	M->speedPID.errorIntegral = 0;
	M->posPID.errorIntegral = 0;
}
void setPIDPeriod(motor* M)
{
	
}

void getSpeedPID(motor* M)
{
	counter[4]++;
	M->timeConstant = (float)((getMicros() - M->prevMicros) / 1000000.00);
	M->prevMicros = getMicros();
	M->currentSpeed = (float)(M->currentPos - M->prevPos) / M->timeConstant * 60.00 / M->parameter.encCPR;
	M->prevPos = M->currentPos;
	
	M->speedPID.error = (float) M->targetedSpeed - M->currentSpeed;
	M->speedPID.errorIntegral += (float) M->speedPID.error*M->timeConstant;
	M->speedPID.errorDerivative = (float) (M->speedPID.error - M->speedPID.prevError) / M->timeConstant;
	
	M->speedPID.prevError = M->speedPID.error;
	M->speedPID.resultedP = M->parameter.speedKp*M->speedPID.error;
	M->speedPID.resultedI = M->parameter.speedKi*M->speedPID.errorIntegral;
	M->speedPID.resultedD = M->parameter.speedKd*M->speedPID.errorDerivative;
	M->speedPID.result = M->speedPID.resultedP + M->speedPID.resultedI + M->speedPID.resultedD;
						 
	if (M->speedPID.result > 4200)
	{
		M->pwm = 4200;
		M->dir = 0x01;
	}
	else if (M->speedPID.result > 0)
	{
		M->pwm = M->speedPID.result;
		M->dir = 0x01;
	}
	else if (M->speedPID.result > -4200)
	{
		M->pwm = -M->speedPID.result;
		M->dir = 0x02;
	}
	else
	{
		M->pwm = 4200;
		M->pwm = 0x02;
	}
	
}
void getPosPID(motor* M)
{
	M->timeConstant = (float)((getMicros() - M->prevMicros) / 1000000.00);
	M->prevMicros = getMicros();
	M->currentSpeed = (float)(M->currentPos - M->prevPos) / M->timeConstant * 60 / M->parameter.encCPR;
	
	M->posPID.error = M->targetedPos - M->currentPos;
	M->posPID.errorIntegral += (float)M->posPID.error*M->timeConstant;
	M->posPID.errorDerivative = (float)(M->posPID.error - M->posPID.prevError)/(M->timeConstant);
	
	M->prevPos = M->currentPos;
	M->posPID.resultedP = M->parameter.speedKp*M->posPID.error;
	M->posPID.resultedI = M->parameter.speedKi*M->posPID.errorIntegral;
	M->posPID.resultedD = M->parameter.speedKd*M->posPID.errorDerivative;
	M->posPID.result = M->posPID.resultedP + M->posPID.resultedI + M->posPID.resultedD;
	if (M->posPID.result > M->parameter.maxSpeed)
	{
		M->targetedSpeed = M->parameter.maxSpeed;
	}
	else if (M->posPID.result < -(M->parameter.maxSpeed))
	{
		M->targetedSpeed = -(M->parameter.maxSpeed);
	}
	else
	{
		M->targetedSpeed = M->posPID.result;
	}
	M->posPID.prevError = M->posPID.error;
	
	M->speedPID.error = M->targetedSpeed - M->currentSpeed;
	M->speedPID.errorIntegral += M->speedPID.error*M->timeConstant;
	M->speedPID.errorDerivative = (M->speedPID.error - M->speedPID.prevError) / M->timeConstant;
	
	M->speedPID.prevError = M->speedPID.error;
	
	M->speedPID.resultedP = M->parameter.speedKp*M->speedPID.error;
	M->speedPID.resultedI = M->parameter.speedKi*M->speedPID.errorIntegral;
	M->speedPID.resultedD = M->parameter.speedKd*M->speedPID.errorDerivative;
	M->speedPID.result = M->speedPID.resultedP + M->speedPID.resultedI + M->speedPID.resultedD;
	
	if (M->speedPID.result > 4200)
	{
		M->pwm = 4200;
		M->dir = 0x01;
	}
	else if (M->speedPID.result > 0)
	{
		M->pwm = M->speedPID.result;
		M->dir = 0x01;
	}
	else if (M->speedPID.result > -4200)
	{
		M->pwm = -M->speedPID.result;
		M->dir = 0x02;
	}
	else
	{
		M->pwm = 4200;
		M->pwm = 0x02;
	}
	
	
}