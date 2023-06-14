#include <stm32f407xx.h>
#include "GPIO.h"
#include "CLOCK.h"
#include "directControl.h"

extern uint8_t RXPacket[1024];
extern uint8_t TXPacket[1024];
extern uint64_t counter[10];
extern uint64_t timeOutCounter;
extern uint64_t connectedCounter;

extern uint8_t trash;
extern motorPID_t defaultMotorPID;
extern uint8_t indicator1;
extern uint32_t temp;
extern motor M[4];
extern uint8_t state;
extern uint8_t calculatedCRC;
extern uint8_t receivedCRC;
extern float generalMonitor[10];
extern uint64_t micros;
extern uint16_t buffer;

void motorSetup();
void E12BusSetup();
void encoderSetup();
void writeIn(uint8_t config);
void indicatorSetup();
void microsSetup();
void PID_Initialization();
void cycleSetup();

