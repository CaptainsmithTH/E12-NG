#ifndef REMAP
#define REMAP
#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define JTAG_SWD_1				(uint8_t)0x00
#define JTAG_SWD_2				(uint8_t)0x01
#define JTAG_SWD_3				(uint8_t)0x02
#define JTAG_SWD_4				(uint8_t)0x03
#define NO_REMAP				(uint8_t)0x00
#define PARTIAL_REMAP			(uint8_t)0x01
#define FULL_REMAP				(uint8_t)0x02

void clear_REMAP(void);

void config_JTAG_SWD(uint8_t mode);

void remap_TIMER1(uint8_t mode);
void remap_TIMER2(uint8_t mode);
void remap_TIMER3(uint8_t mode);
void remap_TIMER4(void);
void remap_USART1(void);
void remap_USART2(void);
void remap_I2C1(void);
void remap_SPI1(void);

#endif
