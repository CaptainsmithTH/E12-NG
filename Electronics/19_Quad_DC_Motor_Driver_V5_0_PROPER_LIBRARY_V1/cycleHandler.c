#include "cycleHandler.h"

void runSpeed_CycleHandler(dcMotor* motor)
{
	motor->kinetic.interval = (getMicros() - motor->kinetic.prevMicros) / 1000000.00;
	motor->kinetic.currentSpeed = (motor->kinetic.currentPosition - motor->kinetic.prevPosition) / motor->kinetic.interval * 60;
}