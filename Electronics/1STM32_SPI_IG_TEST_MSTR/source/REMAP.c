#include "REMAP.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32f103xe.h"

void config_JTAG_SWD(uint8_t mode){
	if(mode == JTAG_SWD_1) AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_RESET;
	else if(mode == JTAG_SWD_2) AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_NOJNTRST;
	else if(mode == JTAG_SWD_3) AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
	else if(mode == JTAG_SWD_4) AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;
}

void clear_REMAP(void){
	AFIO->MAPR &= ~(0x071FFFFF);
}

void remap_ADC(void){
	
}


void remap_TIMER1(uint8_t mode){
	if(mode == NO_REMAP) AFIO->MAPR &= ~(AFIO_MAPR_TIM1_REMAP_0 | AFIO_MAPR_TIM1_REMAP_1);
	else if (mode == PARTIAL_REMAP){
		AFIO->MAPR &= ~(AFIO_MAPR_TIM1_REMAP_1);
		AFIO->MAPR |= AFIO_MAPR_TIM1_REMAP_0;
	}
	else if (mode == FULL_REMAP){
		AFIO->MAPR |= AFIO_MAPR_TIM1_REMAP_0 | AFIO_MAPR_TIM1_REMAP_1;
	}
}

void remap_TIMER2(uint8_t mode){
	if(mode == NO_REMAP) AFIO->MAPR &= ~(AFIO_MAPR_TIM2_REMAP_0 | AFIO_MAPR_TIM2_REMAP_1);
	else if (mode == PARTIAL_REMAP){
		AFIO->MAPR &= ~(AFIO_MAPR_TIM2_REMAP_1);
		AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_0;
	}
	else if (mode == FULL_REMAP){
		AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_0 | AFIO_MAPR_TIM2_REMAP_1;
	}
}

void remap_TIMER3(uint8_t mode){
	if(mode == NO_REMAP) AFIO->MAPR &= ~(AFIO_MAPR_TIM3_REMAP_0 | AFIO_MAPR_TIM3_REMAP_1);
	else if (mode == PARTIAL_REMAP){
		AFIO->MAPR &= ~(AFIO_MAPR_TIM3_REMAP_1);
		AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_0;
	}
	else if (mode == FULL_REMAP){
		AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_0 | AFIO_MAPR_TIM3_REMAP_1;
	}
}

void remap_TIMER4(void){
	AFIO->MAPR |= AFIO_MAPR_TIM4_REMAP;
}

void remap_USART1(void){
	AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;
}

void remap_USART2(void){
	AFIO->MAPR |= AFIO_MAPR_USART2_REMAP;
}

void remap_I2C1(void){
	AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
}

void remap_SPI1(void){
	AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;
}
