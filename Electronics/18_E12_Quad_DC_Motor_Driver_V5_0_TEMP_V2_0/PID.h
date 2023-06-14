
#include "PACKET.h"
extern float generalMonitor[10];
#define maxPWM 4200;
extern float timeConstantTest;
void PIDInit(motor* M);
uint64_t getMicros();
extern uint64_t micros;
extern uint64_t counter[10];
extern uint64_t prevMicros;
void getPosPID(motor* M);
void getSpeedPID(motor* M);
void setPIDPeriod(motor* M);

