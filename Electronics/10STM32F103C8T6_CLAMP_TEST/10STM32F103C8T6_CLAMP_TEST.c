#include "source/E12_STM32_Rx.h"


int main()
{
	general_Setup();
	pinMode(GPIOA, 8, INPUT, FLOATING);
	pinMode(GPIOA, 9, INPUT, FLOATING);
	pinMode(GPIOA, 10, INPUT, FLOATING);
	pinMode(GPIOA, 11, INPUT, FLOATING);
	pinMode(GPIOA, 12, INPUT, FLOATING);
	pinMode(GPIOA, 15, INPUT, FLOATING);
	pinMode(GPIOB, 3, INPUT, FLOATING);
	pinMode(GPIOB, 4, INPUT, FLOATING);
	pinMode(GPIOB, 5, INPUT, FLOATING);
	pinMode(GPIOB, 6, INPUT, FLOATING);
	pinMode(GPIOB, 7, INPUT, FLOATING);
	pinMode(GPIOB, 8, INPUT, FLOATING);
	pinMode(GPIOB, 9, INPUT, FLOATING);
	pinMode(GPIOB, 12, INPUT, FLOATING);
	pinMode(GPIOB, 13, INPUT, FLOATING);
	pinMode(GPIOB, 14, INPUT, FLOATING);
	pinMode(GPIOB, 15, INPUT, FLOATING);
	pinMode(GPIOC, 13, OUTPUT50, PUSHPULL);
	while (true)
	{
		if (pinRead(GPIOB,12))
		{
			pinWrite(GPIOC, 13, LOW);
		}
		else
		{
			
			pinWrite(GPIOC, 13, HIGH);
		}
	}

}