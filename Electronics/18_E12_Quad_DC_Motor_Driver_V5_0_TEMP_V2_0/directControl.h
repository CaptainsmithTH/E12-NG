#include <stm32f4xx.h>
#include <stdlib.h>
#include "PID.h"

extern uint8_t inConfig;
void processMotor(motor* M);
void driveMotor(motor* M);

