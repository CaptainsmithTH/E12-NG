#include <GPIO.h>

void pinMode(GPIO_TypeDef* port ,uint8_t number,uint8_t mode)
{
	port->OSPEEDR |= (0b11 << number * 2);
	port->MODER &= ~(0b11 << number * 2);
	port->MODER |= mode << number * 2;
}

void pinType(GPIO_TypeDef* port, uint8_t number, uint8_t type)
{
	port->OTYPER &= ~(1 << number);
	port->OTYPER |= type << number;
}

void pinWrite(GPIO_TypeDef* port, uint8_t number, uint8_t state)
{
	if (state)
	{
		port->ODR |= (1 << number);
	}
	else
	{
		
		port->ODR &= ~(1 << number);
	}
}

void pinSet(GPIO_TypeDef* port,uint8_t number)
{
	port->BSRR |= (1 << number);
}

void pinReset(GPIO_TypeDef* port, uint8_t number)
{
	port->BSRR |= (1 << (number + 16));
}

void pinToggle(GPIO_TypeDef* port, uint8_t number)
{
	port->ODR ^= (1 << number);
}

void pinSpeed(GPIO_TypeDef* port, uint8_t number, uint8_t speed)
{
	port->OSPEEDR &= ~(0b11 << number * 2);
	port->OSPEEDR |= speed << number * 2;
}

uint8_t pinRead(GPIO_TypeDef* port, uint8_t number)
{
	return (port->IDR & (1 << number)) >> number;
}

void pinAlt(GPIO_TypeDef* port, uint8_t number, uint8_t alt)
{
	if (number < 8)
	{
		port->AFR[0] &= ~(0b1111 << number * 4);
		port->AFR[0] |= (alt << number * 4);
	}
	else
	{
		number = number - 8;
		port->AFR[1] &= ~(0b1111 << number * 4);
		port->AFR[1] |= (alt << number * 4);	
	}
}	   

void pinPull(GPIO_TypeDef* port, uint8_t number, uint8_t pull)
{
	port->PUPDR &= ~(0b11 << number * 2);
	port->PUPDR |= pull << number * 2;
}


