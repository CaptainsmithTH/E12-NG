#include <stm32f407xx.h>

#ifndef GPIO_INCLUDED
#define GPIO_INCLUDED

#define INPUT				0x00
#define OUTPUT				0x01
#define ALTFUNCTION			0x02
#define ANALOG				0x03

#define PUSHPULL			0x00
#define OPENDRAIN			0x01

#define LOWSPEED			0x00
#define MEDIUMSPEED			0x01
#define HIGHSPEED			0x02
#define	VERYHIGHSPEED		0x03

#define FLOATING			0x00
#define PULLUP				0x01
#define PULLDOWN			0x02

#define RISING				0x00
#define FALLING				0x01
#define CHANGE				0x02


void pinMode(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t mode);
void pinSpeed(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t speed);
void pinPull(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t pull);
uint8_t pinRead(GPIO_TypeDef *port, uint8_t pinNumber);
void pinAlt(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t channel);
void attachInterrupt(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t edge);
void clearInterrupt(GPIO_TypeDef *port, uint8_t pinNumber);

#endif