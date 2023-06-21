#include "PWR.h"

uint8_t PWR_setVOSScale(uint8_t vosScale)
{
	PWR->SRDCR &= ~PWR_SRDCR_VOS_Msk;
	PWR->SRDCR |= vosScale << PWR_SRDCR_VOS_Pos;
	uint32_t timeOutCounter = 0;
	while (!(PWR->SRDCR & PWR_SRDCR_VOSRDY))
	{
		timeOutCounter++;
		if (timeOutCounter > timeOut)
		{
			return E12_TIMEOUT;
		}
	}
	return 0;
}

uint8_t PWR_setSelectLDO()
{
	PWR->CR3 |= PWR_CR3_LDOEN;
	uint32_t timeOutCounter = 0;
	while (!(PWR->CSR1 & PWR_CSR1_ACTVOSRDY))
	{
		timeOutCounter++;
		if (timeOutCounter > timeOut)
		{
			return E12_TIMEOUT;
		}
	}
	return 0;
}

void PWR_setSVOS()
{
	PWR->CR1 |= PWR_CR1_SVOS_0 | PWR_CR1_SVOS_1;
}