
#include "SETUP.h"
#define errorIntegralMax 8000
extern float generalMonitor[10];
#define maxPWM 4200;
extern float timeConstantTest;
void PIDInit(motor* M);
uint64_t getMicros();
extern uint64_t counter[10];
extern uint64_t prevMicros;
int16_t getPosPID(motor* M);
int16_t getSpeedPID(motor* M);
void setPIDPeriod(motor* M);