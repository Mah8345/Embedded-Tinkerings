#pragma once

#include <stm32f103xb.h>


enum Mode {Input,Output};

void GPIO_PortsInit(void);
void GPIO_A_0_7_SetMode(enum Mode mode);
void GPIO_B_0_2_SetMode(enum Mode mode);
