#include "stm32l431xx.h"
#include "stdint.h"

#define INPUT			0x00
#define OUTPUT			0x01
#define ALTFUNC			0x02
#define ANALOG			0x03

#define PUSHPULL		0x00
#define OPENDRAIN		0x01

#define FLOATING		0x00
#define PULLUP			0x01
#define PULLDOWN		0x02

#define LOWSPEED		0x00
#define MEDIUMSPEED		0x01
#define	HIGHSPEED		0x02
#define VERYHIGHSPEED	0x03

#define LOW				0x00
#define HIGH			0x01

void pinMode(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t mode, uint8_t type);
void pinSpeed(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t speed);
void pinWrite(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t state);
void pinSet(GPIO_TypeDef *port, uint8_t pinNumber);
void pinReset(GPIO_TypeDef *port, uint8_t pinNumber);
void pinToggle(GPIO_TypeDef *port, uint8_t pinNumber);

#
