#include "pid.h"

PID_t initPID = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
void PIDCalculator(PID_t* controller)
{
	controller->interval = (getMicros() - controller->prevMicros) / 1000000.00;
	controller->prevMicros = getMicros();
	controller->error = controller->targeted - controller->current;
	controller->integralError += controller->error * controller->interval;
	controller->derivativeError = (controller->error - controller->prevError) / controller->interval;
	controller->prevError = controller->error;
	controller->resultedP = controller->kp * controller->error;
	controller->resultedI = controller->ki * controller->integralError;
	controller->resultedD = controller->kd * controller->derivativeError;
	controller->resultedPID = controller->resultedP + controller->resultedI + controller->resultedD;
}
void PIDInit(PID_t* controller)
{
	controller->integralError = 0;
	controller->prevMicros = 0;
	controller->prevError = 0;
}