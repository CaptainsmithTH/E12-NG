#include "PACKET.h"
void exportHeader(uint8_t* TXPacket)
{
	*(uint32_t *)(TXPacket) = returnHeader;
	*(uint16_t *)(TXPacket + typeIDOffset) = typeID;
	*(uint16_t *)(TXPacket + deviceIDOffset) = deviceID;
	*(uint32_t *)(TXPacket + statusOffset) = status; 
}

void statusErrorHandler()
{
	
}

void updateSpeedControl(motor* Motor)
{
	Motor->targetedSpeed = Motor->speedControl.targetedSpd;
}

void updatePositionControl(motor* Motor)
{
	Motor->targetedPos = Motor->positionControl.targetedPos;
}

void updateDirectControl(motor* Motor)
{
	Motor->dir = Motor->directControl.dir;
	Motor->pwm = Motor->directControl.pwm;
}

uint8_t RXPacketProcess(uint8_t* RXPacket,motor* M)
{
	if (SPI1->SR & SPI_SR_CRCERR)
	{
		SPI1->SR &= ~SPI_SR_CRCERR;
		status |= (1 << packetCRCError);
		return packetCRCError;
	}
	status &= ~(1 << packetCRCError);
	
	if (*(uint32_t *)(RXPacket) != receiveHeader)
	{
		status |= (1 << packetHeaderError);
		return packetHeaderError;
	}
	status &= ~(1 << packetHeaderError);
	
	if (*(uint16_t *)(RXPacket + typeIDOffset) != typeID)
	{
		status |= (1 << packetTypeIDError);
		return packetTypeIDError;
	} 
	status &= ~(1 << packetTypeIDError);
	
	if (*(uint16_t *)(RXPacket + deviceIDOffset) != typeID)
	{
		status |= (1 << packetDeviceIDError);
		return packetDeviceIDError;
	} 
	status &= ~(1 << packetDeviceIDError);
	
	if (*(uint32_t *)(RXPacket + statusOffset))
	{
		statusErrorHandler();
		status |= (1 << packetStatusError);
		return packetStatusError;
	}
	status &= ~(1 << packetStatusError);
	
	for (uint8_t i = 0; i < 4; i++)
	{
		if (*(uint16_t *)(RXPacket + headerOffset + perMotorLength*i + cmdOffset) == motorParameterCMD)
		{
			M[i].parameter = *(motorParameter_t *)(RXPacket + headerOffset + perMotorLength*i);
			M[i].returnMode = motorParameterCMD;
			
			status &= ~(1 << (packetCMD1Error + i));
		}
		else if (*(uint16_t *)(RXPacket + headerOffset + perMotorLength*i + cmdOffset) == motorParameterReadCMD)
		{
			M[i].returnMode = motorParameterReadCMD;
			
			status &= ~(1 << (packetCMD1Error + i));
		}
		else if (*(uint16_t *)(RXPacket + headerOffset + perMotorLength*i + cmdOffset) == speedControlCMD)
		{
			M[i].speedControl = *(speedControl_t *)(RXPacket + headerOffset + perMotorLength*i);
			M[i].returnMode = speedControlCMD;
			updateSpeedControl(&M[i]);
			M[i].mode = speedControlCMD;
			
			status &= ~(1 << (packetCMD1Error + i));
		}
		else if (*(uint16_t *)(RXPacket + headerOffset + perMotorLength*i + cmdOffset) == positionControlCMD)
		{
			M[i].positionControl = *(positionControl_t *)(RXPacket + headerOffset + perMotorLength*i);
			M[i].returnMode = positionControlCMD;
			updatePositionControl(&M[i]);
			M[i].mode = positionControlCMD;
			
			status &= ~(1 << (packetCMD1Error + i));
		}
		else if (*(uint16_t *)(RXPacket + headerOffset + perMotorLength*i + cmdOffset) == directControlCMD)
		{
			M[i].directControl = *(directControl_t *)(RXPacket + headerOffset + perMotorLength*i);
			M[i].returnMode = directControlCMD;
			updateDirectControl(&M[i]);
			M[i].mode = directControlCMD;
		}
		else
		{
			status |= (1 << packetCMDError);
			status |= (1 << (packetCMD1Error + i));
			
		}
		
	}
	if(!(status & (0xF << packetCMD1Error))){
		status &= ~(1 << packetCMDError);
	}
	if (status & (1 << packetCMDError))
	{
		return packetCMDError;
	}
	
	return 0;
	
}

void exportParameter(motor* Motor)
{
	Motor->parameter.posResultedP= Motor->posPID.resultedP;
	Motor->parameter.posResultedI = Motor->posPID.resultedI;
	Motor->parameter.posResultedD = Motor->posPID.resultedD;
	Motor->parameter.posResultedPID = Motor->posPID.result;
	Motor->parameter.speedResultedP = Motor->speedPID.resultedP;
	Motor->parameter.speedResultedI = Motor->speedPID.resultedI;
	Motor->parameter.speedResultedD = Motor->speedPID.resultedD;
	Motor->parameter.speedResultedPID = Motor->speedPID.result;
	Motor->parameter.pwm = Motor->pwm;
	Motor->parameter.dir = Motor->dir;
}

void exportSpeedControl(motor* Motor)
{
	Motor->speedControl.status = Motor->status;
	Motor->speedControl.currentPos = Motor->currentPos;
	Motor->speedControl.currentSpd = Motor->currentSpeed;
	Motor->speedControl.targetedSpd = Motor->targetedSpeed;
}

void exportPositionControl(motor* Motor)
{
	Motor->positionControl.status = Motor->status;
	Motor->positionControl.currentPos = Motor->currentPos;
	Motor->positionControl.currentSpd = Motor->currentSpeed;
	Motor->positionControl.targetedSpd = Motor->targetedSpeed;
	Motor->positionControl.targetedPos = Motor->targetedPos;
}

void exportDirectControl(motor* Motor)
{
	Motor->directControl.dir = Motor->dir;
	Motor->directControl.pwm = Motor->pwm;
}

uint8_t TXPacketProcess(uint8_t* TXPacket,motor* M)
{
	exportHeader(TXPacket);
	if (status & generalErrorMsk)
	{
		return 1;
	}
	else
	{
		
		for (uint8_t i = 0; i < 4; i++)
		{
			if (status & (1 << (packetCMDError + 1 + i)))
			{
				*(uint16_t *)(cmdTotalOffset) = CMDerrorCMD;
				
			}
			else
			{
				
				switch (M[i].returnMode)
				{
				case motorParameterCMD :
					exportParameter(&M[i]);
					*(motorParameter_t *)(motorTotalOffset) = M[i].parameter;
					*(uint16_t *)(cmdTotalOffset) = motorParameterCMD;
					break;
				case motorParameterReadCMD :
					exportParameter(&M[i]);
					*(motorParameter_t *)(motorTotalOffset) = M[i].parameter;
					*(uint16_t *)(cmdTotalOffset) = motorParameterReadCMD;
					break;
				case speedControlCMD:
					exportSpeedControl(&M[i]);
					*(speedControl_t *)(motorTotalOffset) = M[i].speedControl;
					*(uint16_t *)(cmdTotalOffset) = speedControlCMD;
					break;
				case positionControlCMD:
					exportPositionControl(&M[i]);
					*(positionControl_t *)(motorTotalOffset) = M[i].positionControl;
					*(uint16_t *)(cmdTotalOffset) = positionControlCMD;
					break;
				case directControlCMD:
					exportDirectControl(&M[i]);
					*(directControl_t *)(motorTotalOffset) = M[i].directControl;
					*(uint16_t *)(cmdTotalOffset) = positionControlCMD;
					
				}
				
			}
		}
	}
	
	if (status & (1 << packetCMDError))
	{
		return 2;
	}
	return 0;
}
