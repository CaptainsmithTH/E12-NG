#include "directControl.h"
void processMotor(motor* M)
{
	switch (M->mode)
	{
	case speedControlCMD:
		getSpeedPID(M);
		break;
	case positionControlCMD:
		getPosPID(M);
		break;
	case directControlCMD:
		M->pwm = M->directControl.pwm;
		M->dir = M->directControl.dir;
		break;
	}
}

void driveMotor(motor* M)
{
	*(uint32_t *)M->channel = M->pwm;
	inConfig |= M->dir << (M->number * 2);
	inConfig &= (~(0b11) | M->dir) << (M->number * 2);
}
