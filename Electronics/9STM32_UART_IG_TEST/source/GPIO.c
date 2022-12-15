#include "GPIO.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stm32f103xe.h"

void pinMode(GPIO_TypeDef *port,uint8_t pin_Number,uint8_t pin_Mode,uint8_t pin_Config){
		if(pin_Number<8){
			if(pin_Mode == INPUT){
				//MODE REGISTER
				port->CRL &= ~((1<<((pin_Number*4)+1)) | (1<<(pin_Number*4)));
				
				//CNF REGISTER
				if(pin_Config == ANALOG){
					port->CRL &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == FLOATING){
					port->CRL &= ~(1<<((pin_Number*4)+3));
					port->CRL |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == PULLUP){
					port->CRL &= ~(1<<((pin_Number*4)+2));
					port->CRL |= 1<<((pin_Number*4)+3);
					port->ODR |= 1<<pin_Number;
				}
				else if(pin_Config == PULLDOWN){
					port->CRL &= ~(1<<((pin_Number*4)+2));
					port->CRL |= 1<<((pin_Number*4)+3);
					port->ODR &= ~(1<<(pin_Number));
				}
			}
			else if(pin_Mode == OUTPUT10){
				//MODE REGISTER
				port->CRL &= ~(1<<((pin_Number*4)+1));
				port->CRL |= 1<<(pin_Number*4);
				
				//CNF REGISTER
				if(pin_Config == PUSHPULL){
					port->CRL &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == OPENDRAIN){
					port->CRL &= ~(1<<((pin_Number*4)+3));
					port->CRL |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == ALTPUSHPULL){
					port->CRL &= ~(1<<((pin_Number*4)+2));
					port->CRL |= 1<<((pin_Number*4)+3);
				}
				else if(pin_Config == ALTOPENDRAIN){
					port->CRL |= (1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2));
				}
					
			}
			else if(pin_Mode == OUTPUT2){
				//MODE REGISTER
				port->CRL &= ~(1<<(pin_Number*4));
				port->CRL |= 1<<((pin_Number*4)+1);
				
				
				//CNF REGISTER
				if(pin_Config == PUSHPULL){
					port->CRL &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == OPENDRAIN){
					port->CRL &= ~(1<<((pin_Number*4)+3));
					port->CRL |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == ALTPUSHPULL){
					port->CRL &= ~(1<<((pin_Number*4)+2));
					port->CRL |= 1<<((pin_Number*4)+3);
				}
				else if(pin_Config == ALTOPENDRAIN){
					port->CRL |= (1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2));
				}
			}
			else if(pin_Mode == OUTPUT50){
				//MODE REGISTER
				port->CRL |= 1<<((pin_Number*4)+1) | 1<<(pin_Number*4);
				
				//CNF REGISTER
				if(pin_Config == PUSHPULL){
					port->CRL &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == OPENDRAIN){
					port->CRL &= ~(1<<((pin_Number*4)+3));
					port->CRL |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == ALTPUSHPULL){
					port->CRL &= ~(1<<((pin_Number*4)+2));
					port->CRL |= 1<<((pin_Number*4)+3);
				}
				else if(pin_Config == ALTOPENDRAIN){
					port->CRL |= (1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2));
				}
			}
			else{
				
			}
		}
		
		
		else if(pin_Number < 16){
			pin_Number -= 8;
			if(pin_Mode == INPUT){
				//MODE REGISTER
				port->CRH &= ~((1<<((pin_Number*4)+1)) | (1<<(pin_Number*4)));
				
				//CNF REGISTER
				if(pin_Config == ANALOG){
					port->CRH &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == FLOATING){
					port->CRH &= ~(1<<((pin_Number*4)+3));
					port->CRH |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == PULLUP){
					port->CRH &= ~(1<<((pin_Number*4)+2));
					port->CRH |= 1<<((pin_Number*4)+3);
					port->ODR |= 1<<(pin_Number+8);			
				}
				else if(pin_Config == PULLDOWN){
					port->CRH &= ~(1<<((pin_Number*4)+2));
					port->CRH |= 1<<((pin_Number*4)+3);
					port->ODR &= ~(1<<(pin_Number+8));
				}
			}
			else if(pin_Mode == OUTPUT10){
				//MODE REGISTER
				port->CRH &= ~(1<<((pin_Number*4)+1));
				port->CRH |= 1<<(pin_Number*4);
				
				//CNF REGISTER
				if(pin_Config == PUSHPULL){
					port->CRH &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == OPENDRAIN){
					port->CRH &= ~(1<<((pin_Number*4)+3));
					port->CRH |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == ALTPUSHPULL){
					port->CRH &= ~(1<<((pin_Number*4)+2));
					port->CRH |= 1<<((pin_Number*4)+3);
				}
				else if(pin_Config == ALTOPENDRAIN){
					port->CRH |= (1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2));
				}
					
			}
			else if(pin_Mode == OUTPUT2){
				//MODE REGISTER
				port->CRH &= ~(1<<(pin_Number*4));
				port->CRH |= 1<<((pin_Number*4)+1);
				
				//CNF REGISTER
				if(pin_Config == PUSHPULL){
					port->CRH &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == OPENDRAIN){
					port->CRH &= ~(1<<((pin_Number*4)+3));
					port->CRH |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == ALTPUSHPULL){
					port->CRH &= ~(1<<((pin_Number*4)+2));
					port->CRH |= 1<<((pin_Number*4)+3);
				}
				else if(pin_Config == ALTOPENDRAIN){
					port->CRH |= (1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2));
				}
			}
			else if(pin_Mode == OUTPUT50){
				//MODE REGISTER
				port->CRH |= 1<<((pin_Number*4)+1) | 1<<(pin_Number*4);
				
				//CNF REGISTER
				if(pin_Config == PUSHPULL){
					port->CRH &= ~((1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2)));
				}
				else if(pin_Config == OPENDRAIN){
					port->CRH &= ~(1<<((pin_Number*4)+3));
					port->CRH |= 1<<((pin_Number*4)+2);
				}
				else if(pin_Config == ALTPUSHPULL){
					port->CRH &= ~(1<<((pin_Number*4)+2));
					port->CRH |= 1<<((pin_Number*4)+3);
				}
				else if(pin_Config == ALTOPENDRAIN){
					port->CRH |= (1<<((pin_Number*4)+3)) | (1<<((pin_Number*4)+2));
				}
			}
			else{
				
			}
			
		}
		else{
		
		}
	}

void pinWrite(GPIO_TypeDef *port,uint8_t pin_Number,uint8_t pin_State){
	if(pin_State){
		port->BSRR |= (1<<pin_Number);
	}
	else{
		port->BSRR |= (1<<(pin_Number+16));
	}
	
}
void pinToggle(GPIO_TypeDef *port,uint8_t pin_Number){
	port->ODR ^= 1<<pin_Number;
}
uint8_t pinRead(GPIO_TypeDef *port,uint8_t pin_Number){
	if((port->IDR >> pin_Number) & 1){
		return 1;
	}
	else{
		return 0;
	}
}

//External Interrupt
//===============================================

void attachInterrupt(GPIO_TypeDef *port,uint8_t pin_Number,uint8_t interrupt_Edge){
	if(port == GPIOA){
			switch(pin_Number){
				case 0 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA;
				break;
				case 1 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PA;
				break;
				case 2 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PA;
				break;
				case 3 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PA;
				break;
				case 4 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI0_PA;
				break;
				case 5 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI1_PA;
				break;
				case 6 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI2_PA;
				break;
				case 7 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI3_PA;
				break;
				case 8 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI0_PA;
				break;
				case 9 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI1_PA;
				break;
				case 10 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI2_PA;
				break;
				case 11 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI3_PA;
				break;
				case 12 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI0_PA;
				break;
				case 13 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI1_PA;
				break;
				case 14 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI2_PA;
				break;
				case 15 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI3_PA;
				break;
				
				
			}
	}
	else if (port == GPIOB){
		switch(pin_Number){
			case 0 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PB;
			break;
			case 1 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PB;
			break;
			case 2 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PB;
			break;
			case 3 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PB;
			break;
			case 4 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI0_PB;
			break;
			case 5 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI1_PB;
			break;
			case 6 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI2_PB;
			break;
			case 7 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI3_PB;
			break;
			case 8 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI0_PB;
			break;
			case 9 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI1_PB;
			break;
			case 10 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI2_PB;
			break;
			case 11 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI3_PB;
			break;
			case 12 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI0_PB;
			break;
			case 13 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI1_PB;
			break;
			case 14 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI2_PB;
			break;
			case 15 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI3_PB;
			break;
		}
	}
	else if (port == GPIOC){
		switch(pin_Number){
			case 0 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PC;
			break;
			case 1 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PC;
			break;
			case 2 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PC;
			break;
			case 3 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PC;
			break;
			case 4 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI0_PC;
			break;
			case 5 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI1_PC;
			break;
			case 6 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI2_PC;
			break;
			case 7 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI3_PC;
			break;
			case 8 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI0_PC;
			break;
			case 9 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI1_PC;
			break;
			case 10 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI2_PC;
			break;
			case 11 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI3_PC;
			break;
			case 12 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI0_PC;
			break;
			case 13 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI1_PC;
			break;
			case 14 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI2_PC;
			break;
			case 15 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI3_PC;
			break;
		}
	}
	else if (port == GPIOD){
		switch(pin_Number){
			case 0 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PD;
			break;
			case 1 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PD;
			break;
			case 2 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PD;
			break;
			case 3 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PD;
			break;
			case 4 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI0_PD;
			break;
			case 5 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI1_PD;
			break;
			case 6 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI2_PD;
			break;
			case 7 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI3_PD;
			break;
			case 8 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI0_PD;
			break;
			case 9 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI1_PD;
			break;
			case 10 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI2_PD;
			break;
			case 11 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI3_PD;
			break;
			case 12 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI0_PD;
			break;
			case 13 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI1_PD;
			break;
			case 14 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI2_PD;
			break;
			case 15 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI3_PD;
			break;
		}
	}
	else if (port == GPIOE){
		switch(pin_Number){
			case 0 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PE;
			break;
			case 1 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PE;
			break;
			case 2 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PE;
			break;
			case 3 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PE;
			break;
			case 4 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI0_PE;
			break;
			case 5 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI1_PE;
			break;
			case 6 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI2_PE;
			break;
			case 7 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI3_PE;
			break;
			case 8 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI0_PE;
			break;
			case 9 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI1_PE;
			break;
			case 10 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI2_PE;
			break;
			case 11 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI3_PE;
			break;
			case 12 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI0_PE;
			break;
			case 13 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI1_PE;
			break;
			case 14 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI2_PE;
			break;
			case 15 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI3_PE;
			break;
		}
	}
	else if (port == GPIOF){
		switch(pin_Number){
			case 0 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PF;
			break;
			case 1 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PF;
			break;
			case 2 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PF;
			break;
			case 3 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PF;
			break;
			case 4 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI0_PF;
			break;
			case 5 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI1_PF;
			break;
			case 6 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI2_PF;
			break;
			case 7 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI3_PF;
			break;
			case 8 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI0_PF;
			break;
			case 9 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI1_PF;
			break;
			case 10 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI2_PF;
			break;
			case 11 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI3_PF;
			break;
			case 12 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI0_PF;
			break;
			case 13 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI1_PF;
			break;
			case 14 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI2_PF;
			break;
			case 15 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI3_PF;
			break;
		}
	}
	else if (port == GPIOG){
		switch(pin_Number){
			case 0 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PG;
			break;
			case 1 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PG;
			break;
			case 2 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PG;
			break;
			case 3 : AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PG;
			break;
			case 4 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI0_PG;
			break;
			case 5 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI1_PG;
			break;
			case 6 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI2_PG;
			break;
			case 7 : AFIO->EXTICR[1] = AFIO_EXTICR1_EXTI3_PG;
			break;
			case 8 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI0_PG;
			break;
			case 9 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI1_PG;
			break;
			case 10 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI2_PG;
			break;
			case 11 : AFIO->EXTICR[2] = AFIO_EXTICR1_EXTI3_PG;
			break;
			case 12 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI0_PG;
			break;
			case 13 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI1_PG;
			break;
			case 14 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI2_PG;
			break;
			case 15 : AFIO->EXTICR[3] = AFIO_EXTICR1_EXTI3_PG;
			break;
		}
	}
	EXTI->IMR |= (1<<pin_Number);
	if(interrupt_Edge == RISING){
		EXTI->RTSR |= (1<<pin_Number);
	}
	else if (interrupt_Edge == FALLING){
		EXTI->FTSR |= 1<<pin_Number;
	}
	else if (interrupt_Edge == CHANGE){
		EXTI->FTSR |= 1<<pin_Number;
		EXTI->RTSR |= 1<<pin_Number;
	}
	
	
	if(pin_Number < 1){
		NVIC_EnableIRQ(EXTI0_IRQn);
	}
	else if(pin_Number < 2){
		NVIC_EnableIRQ(EXTI1_IRQn);
	}
	else if(pin_Number < 3){
		NVIC_EnableIRQ(EXTI2_IRQn);
	}
	else if(pin_Number < 4){
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
	else if(pin_Number < 5){
		NVIC_EnableIRQ(EXTI4_IRQn);
	}
	else if(pin_Number < 10){
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else if(pin_Number < 16){
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
}

void clearInterrupt(GPIO_TypeDef *port, uint8_t pin_Number){
	if(pin_Number < 4){
		AFIO->EXTICR[0] &= ~(15 << (pin_Number*4));
	}
	else if (pin_Number <8){
		AFIO->EXTICR[1] &= ~(15 << ((pin_Number-4)*4));
	}
	else if (pin_Number <12){
		AFIO->EXTICR[2] &= ~(15 << ((pin_Number-8)*4));
	}
	else if (pin_Number <16){
		AFIO->EXTICR[3] &= ~(15 << ((pin_Number-12)*4));
	}
	EXTI->IMR &= ~(1<<pin_Number);
	EXTI->FTSR &= ~(1<<pin_Number);
	EXTI->RTSR &= ~(1<<pin_Number);
	if(pin_Number < 1){
		NVIC_DisableIRQ(EXTI0_IRQn);
	}
	else if(pin_Number < 2){
		NVIC_DisableIRQ(EXTI1_IRQn);
	}
	else if(pin_Number < 3){
		NVIC_DisableIRQ(EXTI2_IRQn);
	}
	else if(pin_Number < 4){
		NVIC_DisableIRQ(EXTI3_IRQn);
	}
	else if(pin_Number < 5){
		NVIC_DisableIRQ(EXTI4_IRQn);
	}
	
}

void resetInterrupt(GPIO_TypeDef *port, uint8_t pin_Number){
	EXTI->PR |= (1<<pin_Number);
}

