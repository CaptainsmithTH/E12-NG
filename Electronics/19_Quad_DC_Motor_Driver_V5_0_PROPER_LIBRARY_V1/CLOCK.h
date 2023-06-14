#include <stm32f407xx.h>

#ifndef CLOCK_INCLUDED
#define CLOCK_INCLUDED
static uint64_t micros = 0;
void generalSetup();
uint64_t getMicros();
#endif
