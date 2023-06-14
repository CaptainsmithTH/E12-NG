#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include <stm32f4xx.h>
#include "comReturnParameter.h"

#define positionControlCMD					0x57
#define runPositionCMD						0x01
#define runPositionWithLimitedSpeedCMD		0x02
#define runPositionWithTimeoutCMD			0x03
#define runPositionWithLimitedSpeedAndTimeoutCMD 0x04
#define runPositionStopCMD					0x05

typedef struct
{
	int64_t targetedPosition;
	
}runPositionRX_t;
typedef struct
{
	returnPID_t returnPositionPID;
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
	int64_t targetedPosition;
	float targetedSpeed;
	uint32_t status;
	uint32_t currentTime;
	
}runPositionTX_t;
typedef struct 
{
	runPositionRX_t rxBuffer;	
	runPositionTX_t txBuffer;
}runPosition_t;
typedef struct
{
	int64_t targetedPosition;
	float targetedSpeed;

}runPositionWithLimitedSpeedRX_t;
typedef struct
{
	returnPID_t returnPositionPID;
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
	int64_t targetedPosition;
	float targetedSpeed;
	uint32_t status;
	uint32_t currentTime;
}runPositionWithLimitedSpeedTX_t;
typedef struct
{
	runPositionWithLimitedSpeedRX_t rxBuffer;
	runPositionWithLimitedSpeedTX_t txBuffer;
}runPositionWithLimitedSpeed_t ;
typedef struct
{
	int64_t targetedPosition;
	uint32_t time;
}runPositionWithTimeoutRX_t ;
typedef struct
{
	returnPID_t returnPositionPID;
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
	int64_t targetedPosition;
	float targetedSpeed;
	uint32_t status;
	uint32_t time;
	uint32_t currentTime;
}runPositionWithTimeoutTX_t ;
typedef struct
{
	runPositionWithTimeoutRX_t rxBuffer;
	runPositionWithTimeoutTX_t txBuffer;
}runPositionWithTimeout_t;
typedef struct
{
	int64_t targetedPosition;
	float targetedSpeed;
	uint32_t time;
}runPositionWithLimitedSpeedAndTimeoutRX_t;
typedef struct
{
	returnPID_t returnPositionPID;
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
	int64_t targetedPosition;
	float targetedSpeed;
	uint32_t status;
	uint32_t time;
	uint32_t currentTime;
}runPositionWithLimitedSpeedAndTimeoutTX_t;
typedef struct
{
	runPositionWithLimitedSpeedAndTimeoutRX_t rxBuffer;
	runPositionWithLimitedSpeedAndTimeoutTX_t txBuffer;
}runPositionWithLimitedSpeedAndTimeout_t;
typedef struct
{
	
}runPositionStopRX_t;
typedef struct
{
	returnPID_t returnPositionPID;
	returnPID_t returnSpeedPID;
	returnMeasured_t returnMeasured;
	returnMotorPWM_t returnPWM;
}runPositionStopTX_t;
typedef struct
{
	runPositionStopRX_t rxBuffer;
	runPositionStopTX_t txBuffer;
}runPositionStop_t;
typedef struct
{
	runPosition_t runPosition;
	runPositionWithLimitedSpeed_t runPositionWithLimitedSpeed;
	runPositionWithTimeout_t runPositionWithTimeout;
	runPositionWithLimitedSpeedAndTimeout_t runPositionWithLimitedSpeedAndTimeout;
	runPositionStop_t runPositionStop;
}positionControl_t;


