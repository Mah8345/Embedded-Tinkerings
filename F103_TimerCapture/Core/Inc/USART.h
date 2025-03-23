#pragma once

#include <stm32f103xb.h>

void USART_TransmitterPinsInit(void);

void USART_TransmitterInit(void);
void USART_Write(char data);
void USART_SendMessage(char *message, uint32_t messageLength);
