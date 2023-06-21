#include "FLASH.h"

void FLASH_setFlashLatency(uint32_t latency)
{
	FLASH->ACR |= latency;
}