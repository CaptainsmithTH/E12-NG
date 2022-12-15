#include "GPIO.h"

void pinMode(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t mode, uint8_t type)
{
	port->MODER |= mode << (pinNumber * 2);
	port->MODER &= ~((mode ^ 0b11) << pinNumber * 2);
	port->OTYPER |= type << pinNumber;
	port->OTYPER &= ~((type ^ 1) << pinNumber);
	if (mode == OUTPUT)
	{
		port->OSPEEDR |= (3 << (pinNumber * 2));
	}
}

void pinWrite(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t state)
{
	port->BSRR |= state << pinNumber | !state << (pinNumber + 16);
}

void pinSet(GPIO_TypeDef *port, uint8_t pinNumber){
	port->BSRR |= 1 << pinNumber;
}
void pinReset(GPIO_TypeDef *port, uint8_t pinNumber)
{
	port->BSRR |= 1 << (pinNumber + 16);
}

void pinToggle(GPIO_TypeDef *port, uint8_t pinNumber)
{
	port->ODR ^= 1 << (pinNumber);
}