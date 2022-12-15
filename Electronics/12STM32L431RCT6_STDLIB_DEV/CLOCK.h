#include "stm32l431xx.h"
#include "stdint.h"

#define CONFIG1				0x00
#define CONFIG2				0x01
#define CONFIG3				0x02

void setClock160MHZ();
void setClock80MHZ();
void setClock40MHZ();
void setClockFrequency(uint8_t PLLN, uint8_t PLLM, uint8_t PLLR,uint8_t HPRE,uint8_t PPRE1,uint8_t PPRE2);


