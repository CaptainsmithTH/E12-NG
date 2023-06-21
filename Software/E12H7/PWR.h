

#ifndef PWR_INCLUDED
#define PWR_INCLUDED
#include "COMMON.h"

#define VOS_SCALE3			0x00
#define VOS_SCALE2			0x01
#define VOS_SCALE1			0x02
#define VOS_SCALE0			0x03	

uint8_t PWR_setVOSScale(uint8_t vosScale);
uint8_t PWR_setSelectLDO();
void PWR_setSVOS();



#endif
