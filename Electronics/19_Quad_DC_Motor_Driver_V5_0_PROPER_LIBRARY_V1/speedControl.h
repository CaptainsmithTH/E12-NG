#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include <stm32f4xx.h>	 
#include "comReturnParameter.h"

#define speedControlCMD				0x55
#define runSpeedCMD					0x01
#define runSpeedUntilContactCMD		0x02
#define runSpeedForTimeCMD			0x03
#define runSpeedStopCMD				0x04
typedef struct
{
	float targetedSpeed;
}runSpeedRX_t;
typedef struct
{	
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
	float targetedSpeed;
	uint32_t status;
	
}runSpeedTX_t;
typedef struct
{
	runSpeedRX_t rxBuffer;
	runSpeedTX_t txBuffer;
	
}runSpeed_t;
typedef struct
{
	float targetedSpeed;
	float backingOutSpeed;
	float approachingSpeed;
	uint32_t timeOut;
	uint16_t contactSwitchNumber;
}runSpeedUntilContactRX_t;
typedef struct 
{	
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
	float targetedSpeed;
	float backingOutSpeed;
	float approachingSpeed;	
	uint32_t status;
	uint32_t timeOut;
	uint32_t currentTime;
	uint16_t contactSwitchNumber;
	
	
}runSpeedUntilContactTX_t;
typedef struct
{
	runSpeedUntilContactRX_t rxBuffer;
	runSpeedUntilContactTX_t txBuffer;
}runSpeedUntilContact_t;
typedef struct
{
	float targetedSpeed;
	uint32_t time;
}runSpeedForTimeRX_t;
typedef struct
{
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
	float targetedSpeed;
	uint32_t status;
	uint32_t time;
	uint32_t currentTime;
}runSpeedForTimeTX_t;
typedef struct
{
	
}runSpeedStopRX_t;
typedef struct
{
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
}runSpeedStopTX_t;
typedef struct 
{
	runSpeedStopRX_t rxBuffer;
	runSpeedStopTX_t txBuffer;
}runSpeedStop_t;
typedef struct
{
	runSpeed_t runSpeed;
	runSpeedUntilContact_t runSpeedUntilContact;
	runSpeedStop_t runStop;
	
}speedControl_t;

void runSpeed_RXHandler();
void runSpeed_TXHandler();
void runSpeedUntilContact_RXHandler();
void runSpeedUntilContact_TXHandler();
void runSpeedForTime_RXHandler();
void runSpeedForTime_TXHandler();
void runSpeedStop_TXHandler();
void runSpeedStop_RXHandler();


