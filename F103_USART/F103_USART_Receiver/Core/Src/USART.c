#include <USART.h>

void USART_ReceiverPinsInit() {
	//RX pin
	GPIOB->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11); //clear PB11 MODE and CNF bits
	GPIOB->CRH |= (GPIO_CRH_CNF11_0); //set PB11 as floating input
}

void USART_ReceiverInit(void) {
	USART_ReceiverPinsInit();

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

	USART3->CR1 |= USART_CR1_RE; //enable receiver
}

char USART_WaitChar(void) {
	while (!(USART3->SR & USART_SR_RXNE))
		; //wait until data is copied into USART_DR
	char receivedChar = USART3->DR;
	return receivedChar;
}

