#include "main.h"

void USART_ReceiverInit();
void USART_TransmitterInit();
void USART2_IRQHandler();


int main(){
	__disable_irq();
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	USART_ReceiverInit();
	USART_TransmitterInit();
	__enable_irq();
	while(1){

	}
}

void USART_ReceiverInit(){
	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3); //clear PA3 MODE and CNF bits
	GPIOA->CRL |= (GPIO_CRL_MODE3_1 | GPIO_CRL_CNF3_1); //set as alternate function push-pull

	USART2->CR1 |= USART_CR1_UE;
	USART2->CR1 &= ~USART_CR1_M; //8-bit characters
	USART2->CR1 &= ~USART_CR1_PCE; //no parity bit
	USART2->CR1 |= USART_CR1_RXNEIE; //enable RXNE interrupt
	USART2->CR2 &= ~USART_CR2_STOP; //1 stop bit

	USART2->BRR = 0x341; //9600 baud rate

	USART2->CR1 |= USART_CR1_RE;
	NVIC_EnableIRQ(USART2_IRQn);
}

void USART_TransmitterInit(){
	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
	GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1);

	USART2->CR1 |= USART_CR1_TE;
}


char FlipCase(char ch){
	if(ch < 65 || ch > 122) return ch;
	if(ch > 90 && ch < 97) return ch;

	if(ch >= 97) return ch - 32;
	return ch + 32;
}


void USART2_IRQHandler(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
	GPIOC->CRH |= GPIO_CRH_MODE13_1;
	GPIOC->BRR = GPIO_BRR_BR13;
	if(USART2->SR & USART_SR_RXNE){
		char received = USART2->DR;
		while(!(USART2->SR & USART_SR_TXE));
		USART2->DR = FlipCase(received);
		USART2->SR &= ~USART_SR_RXNE;
	}
}
