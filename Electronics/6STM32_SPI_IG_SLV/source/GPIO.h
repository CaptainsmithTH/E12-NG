#ifndef GPIO
#define GPIO
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32f103xe.h"

//DEFINE SECTION
//===================================================

//STATE
#define LOW						(uint8_t)0x00
#define HIGH					(uint8_t)0x01

//GPIO SETUP
#define INPUT 					(uint8_t)0x00
#define OUTPUT10 				(uint8_t)0x01
#define OUTPUT2					(uint8_t)0x02
#define OUTPUT50				(uint8_t)0x03

#define ANALOG					(uint8_t)0x00
#define FLOATING				(uint8_t)0x01
#define PULLUP					(uint8_t)0x02
#define PULLDOWN				(uint8_t)0x03

#define PUSHPULL				(uint8_t)0x00
#define OPENDRAIN				(uint8_t)0x01
#define ALTPUSHPULL				(uint8_t)0x02
#define ALTOPENDRAIN			(uint8_t)0x03

//INTERRUPT
#define RISING					(uint8_t)0x00
#define FALLING					(uint8_t)0x01
#define CHANGE					(uint8_t)0x02


//STANDARD GPIO
void pinMode(GPIO_TypeDef *port,uint8_t pin_Number,uint8_t pin_Mode,uint8_t pin_Config);
void pinWrite(GPIO_TypeDef *port,uint8_t pin_Number,uint8_t pin_State);
void pinToggle(GPIO_TypeDef *port,uint8_t pin_Number);
uint8_t pinRead(GPIO_TypeDef *port,uint8_t pin_Number);

//INTERRUPT
void attachInterrupt(GPIO_TypeDef *port,uint8_t pin_Number,uint8_t interrupt_Edge);
void resetInterrupt(GPIO_TypeDef *port, uint8_t pin_Number);
void clearInterrupt(GPIO_TypeDef *port, uint8_t pin_Number);



#endif
