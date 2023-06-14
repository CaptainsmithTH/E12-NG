#include "GPIO.h"
void pinMode(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t mode)
{
	port->MODER &= ~(0b11 << pinNumber * 2);
	port->MODER |= mode << pinNumber * 2;
	port->OSPEEDR |= 0b11 << pinNumber * 2;
}

void pinSpeed(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t speed)
{
	port->OSPEEDR &= ~(0b11 << pinNumber * 2);
	port->OSPEEDR |= speed << pinNumber * 2;
}

void pinPull(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t pull)
{
	port->PUPDR &= ~(0b11 << pinNumber * 2);
	port->PUPDR |= pull << pinNumber * 2;
	
}

uint8_t pinRead(GPIO_TypeDef *port, uint8_t pinNumber)
{
	return (port->IDR & (1<<pinNumber)) >> pinNumber;
}

void pinAlt(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t channel)
{
	if (pinNumber > 7)
	{
		port->AFR[1] &= ~(0b1111 << (pinNumber - 8) * 4);
		port->AFR[1] |= channel << (pinNumber - 8) * 4;
	}
	else
	{
		port->AFR[0] &= ~(0b1111 << (pinNumber) * 4);
		port->AFR[0] |= channel << (pinNumber) * 4;
	}
}

void attachInterrupt(GPIO_TypeDef *port, uint8_t pinNumber, uint8_t edge)
{
	EXTI->IMR |= (1 << pinNumber);
	if (edge == RISING || edge == CHANGE)
	{
		EXTI->RTSR |= (1 << pinNumber);
	}
	if (edge == FALLING || edge == CHANGE)
	{
		EXTI->FTSR |= (1 << pinNumber);
	}
	if (port == GPIOA)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0000 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOB)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0001 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOC)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0010 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOD)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0011 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOE)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0100 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOF)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0101 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOG)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0110 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOH)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b0111 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
	if (port == GPIOI)
	{
		for (uint8_t i = 0; i < 4; i++)
		{
			if (pinNumber < i * 4)
			{
				SYSCFG->EXTICR[i] &= ~(0b1111 << (pinNumber - i * 4) * 4);
				SYSCFG->EXTICR[i] |= (0b1000 << (pinNumber - i * 4) * 4);
				break;
			}
		}
		return;
	}
}


void clearInterrupt(GPIO_TypeDef *port, uint8_t pinNumber)
{
	if (EXTI->PR & (1 << pinNumber))
	{
		EXTI->PR |= (1 << pinNumber);
	}
}