#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include <stm32f4xx.h>
#include "comReturnParameter.h"

#define pwmControlCMD				0x56
#define runPWMCMD					0x01
#define runPWMUntilContactCMD		0x02
#define runPWMForTimeCMD			0x03
#define runPWMStopCMD				0x04

typedef struct
{
	uint16_t pwm;
	uint16_t dir;
}runPWMRX_t;
typedef struct
{
	uint16_t pwm;
	uint16_t dir;
	returnMotorPWM_t returnPWM;
	
}runPWMTX_t;
typedef struct
{
	runPWMRX_t rxBuffer;
	runPWMTX_t txBuffer;
}runPWM_t;
typedef struct
{
	uint16_t pwm;
	uint16_t dir;
	uint16_t backingOutPWM;
	uint16_t approachingPWM;
	uint32_t timeOut;
	uint16_t contactSwitchNumber;
}runPWMUntilContactRX_t;
typedef struct
{
	returnMotorPWM_t returnPWM;
	uint16_t pwm;
	uint16_t dir;
	uint16_t backingOutPWM;
	uint16_t backingOutdir;
	uint16_t approachingPWM;
	uint16_t approachingdir;
	uint32_t status;
	uint32_t timeOut;
	uint32_t currentTime;
	uint16_t contactSwitchNumber;
	
}runPWMUntilContactTX_t;
typedef struct
{
	runPWMUntilContactRX_t rxBuffer;
	runPWMUntilContactTX_t txBuffer;
}runPWMUntilContact_t;
typedef struct
{
	uint16_t pwm;
	uint16_t dir;
	uint32_t time;
}runPWMForTimeRX_t;
typedef struct
{
	returnMotorPWM_t returnPWM;
	uint16_t pwm;
	uint16_t dir;
	uint32_t status;
	uint32_t time;
	uint32_t currentTime;
}runPWMForTimeTX_t;
typedef struct
{
	runPWMForTimeRX_t rxBuffer;
	runPWMForTimeTX_t txBuffer;
}runPWMForTime_t;
typedef struct
{
	
}runPWMStopRX_t;
typedef struct
{
	returnMotorPWM_t returnPWM;
}runPWMStopTX_t;
typedef struct
{
	runPWMStopRX_t rxBuffer;
	runPWMStopTX_t txBuffer;
}runPWMStop_t;
typedef struct
{
	runPWM_t runPWM;
	runPWMUntilContact_t runPWMUntilContact;
	runPWMForTime_t runPWMForTime;
	runPWMStop_t runPWMStop;
}pwmControl_t;

void runPWM_RXHandler();
void runPWM_TXHandler();
void runPWMUntilContact_RXHandler();
void runPWMUntilContact_TXHandler();
void runPWMForTime_RXHandler();
void runPWMForTime_TXHandler();
void runPWMStop_RXHandler();
void runPWMStop_TXHandler();