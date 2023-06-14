#include <stdint.h>
#include <stm32f4xx.h>
#define receiveHeader		0x63010298
#define returnHeader		0x64010377
#define packetSize			512
#define perMotorLength		120
#define typeID				0x55AA
#define deviceID			0x5500
#define headerOffset		12
#define cmdOffset			118
#define typeIDOffset		4
#define deviceIDOffset		6
#define statusOffset		8
#define cmdTotalOffset		TXPacket + headerOffset + perMotorLength*i + cmdOffset
#define motorTotalOffset	TXPacket + headerOffset + perMotorLength*i
#define generalErrorMsk		0b111111

#define packetNorminal		0x00
#define packetCRCError		0x01
#define packetHeaderError	0x02
#define packetTypeIDError	0x03
#define packetDeviceIDError	0x04
#define packetStatusError	0x05
#define packetCMDError		0x06
#define packetCMD1Error		0x07
#define packetCMD2Error		0x08
#define packetCMD3Error		0x09
#define packetCMD4Error		0x0A

#define motorParameterCMD		0x5501
#define motorParameterReadCMD	0x5502
#define speedControlCMD			0x5503
#define positionControlCMD		0x5504
#define directControlCMD		0x5505
#define CMDerrorCMD				0xAA01

extern uint32_t status;
extern uint32_t test;
extern uint64_t counter[10];

typedef struct
{
	float posKp;
	float posKi;
	float posKd;
	float speedKp;
	float speedKi;
	float speedKd;
	float maxSpeed;
	float posRampCoe;
	float spdRampCoe;
	float encCPR;
	float speedResultedP;
	float speedResultedI;
	float speedResultedD;
	float posResultedP;
	float posResultedI;
	float posResultedD;
	float posResultedPID;
	float speedResultedPID;
	uint16_t encoderDigitalFilter;
	uint16_t PIDPeriodARR;
	int16_t pwm;
	uint16_t dir;
}motorParameter_t;

typedef struct
{
	float targetedSpd;
	int64_t currentPos;
	float currentSpd;
	uint32_t status;
}speedControl_t;

typedef struct
{
	int64_t targetedPos;
	int64_t currentPos;
	float targetedSpd;
	float currentSpd;
	uint32_t status;
}positionControl_t;

typedef struct
{
	uint16_t pwm;
	uint16_t dir;
}directControl_t;

typedef struct 
{
	float resultedP;
	float resultedI;
	float resultedD;
	float errorIntegral;
	float errorDerivative;
	float error;
	float prevError;
	float result;
	
}motorPID_t;

typedef struct
{
	motorParameter_t parameter;
	speedControl_t speedControl;
	positionControl_t positionControl;
	directControl_t directControl;
	motorPID_t speedPID;
	motorPID_t posPID;
	int64_t currentPos;
	int64_t prevPos;
	int64_t targetedPos;
	uint64_t prevMicros;
	float timeConstant;
	float currentSpeed;
	float targetedSpeed;
	
	uint32_t returnMode;
	uint32_t mode;
	uint32_t status;
	
	uint16_t pwm;
	uint16_t dir;
	uint16_t prevDir;
	
	
}motor;

extern float generalMonitor[10];
uint8_t RXPacketProcess(uint8_t* RXPacket, motor* M);
uint8_t TXPacketProcess(uint8_t* TXPacket, motor* M);



