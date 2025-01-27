#pragma once
#include <stm32f103xb.h>

enum Mode {Input, Output};
void GPIO_A_4_7_SetMode(enum Mode mode);
void GPIO_A_0_2_SetOutputMode(void);
void GPIO_Init(void);
