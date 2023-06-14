#ifndef GPIO_H
#define GPIO_H
#include "COMMON.h"

#define INPUT 0x00
#define OUTPUT 0x01
#define ALT 0x02
#define ANALOG 0x03


#define PUSHPULL 0x00
#define OPENDRAIN 0x01

#define LOWSPEED 0x00
#define MEDSPEED 0x01
#define HIGHSPEED 0x02
#define MAXSPEED 0x03

#define NOPULL 0x00
#define PULLUP 0x01
#define PULLDOWN 0x02


void pinMode(GPIO_TypeDef* port, uint8_t number, uint8_t mode);
void pinType(GPIO_TypeDef* port, uint8_t number, uint8_t type);
void pinWrite(GPIO_TypeDef* port, uint8_t number, uint8_t state);
void pinSet(GPIO_TypeDef* port, uint8_t number);
void pinReset(GPIO_TypeDef* port, uint8_t number);
void pinToggle(GPIO_TypeDef* port, uint8_t number);
void pinSpeed(GPIO_TypeDef* port, uint8_t number, uint8_t speed);
uint8_t pinRead(GPIO_TypeDef* port, uint8_t number);
void pinAlt(GPIO_TypeDef* port, uint8_t number, uint8_t alt);
void pinPull(GPIO_TypeDef* port, uint8_t number, uint8_t pull);
#endif