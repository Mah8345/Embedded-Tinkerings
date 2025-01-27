#pragma once

#include <stm32f103xb.h>

void USART_ReceiverPinsInit(void);

void USART_ReceiverInit(void);
char USART_WaitChar(void);
