#include <USART.h>

void USART_TransmitterPinsInit() {
	//TX pin
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10); //clear PB10 MODE and CNF bits
	GPIOB->CRH |= (GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1); //set PB10 as push-pull alternate function output 2MHz
}

void USART_TransmitterInit() {
	USART_TransmitterPinsInit();

	RCC->APB1ENR |= RCC_APB1ENR_USART3EN; //enable clock for USART3
	USART3->CR1 |= USART_CR1_UE; //enabling USART3
	USART3->CR1 &= ~USART_CR1_M; //8-bit characters
	USART3->CR1 &= ~USART_CR1_PCE; //no parity bit
	USART3->CR2 &= ~USART_CR2_STOP; //one stop bit

	//configuring a 9600 baud rate:
	//9600 = input_clock/(16 * USARTDIV) -> 9600 = 8,000,000/(16 * USARTDIV)
	//->USARTDIV = 8,000,000/(16 * 9600) = 52.08 -> DIV_Mantissa = 0x34
	//DIV_Fraction = 16 * 0.08 = 1.28 -> DIV_Fraction = 0x1;
	//therefore USART_BRR = 0x341
	USART3->BRR = 0x341;

	USART3->CR1 |= USART_CR1_TE; //enable transmitter
}

void USART_Write(char data) {
	while (!(USART3->SR & USART_SR_TXE))
		; //wait until TDR is empty
	USART3->DR = data;
}

void USART_SendMessage(char *message, uint32_t messageLength) {
	for (int i = 0; i < messageLength; i++) {
		USART_Write(message[i]);
	}
}


