#include "main.h"
#include "stdbool.h"

#define BUFFER_SIZE 100
volatile char txBuffer[BUFFER_SIZE];
volatile int txHead = 0, txTail = 0;
volatile int txCount = 0;
volatile bool txBusy = false;

void USART_Transfer(char *message);
void USART_TransmitterInit();
void USART2_IRQHandler();

int main() {
	USART_TransmitterInit();

	while (1) {
		USART_Transfer("Embedded Tinkerings\r\n");
		for (int i = 0; i < 2000000; i++)
			;
	}
}

void USART_Transfer(char *message) {
	while (*message) {
		while (txCount == BUFFER_SIZE)
			; //wait, buffer is full

		//disabling interrupts before filling the buffer is only necessary when filling is done in an ISR (which doesn't happen in this code)
		int primask = __get_PRIMASK(); //get global status of interrupts (masked/not masked)
		__disable_irq();
		txBuffer[txHead] = *message;
		txHead = (txHead + 1) % BUFFER_SIZE;
		message++;
		txCount++;
		__set_PRIMASK(primask); //set global status of interrupts according to what it was before the critical section
	}

	if (!txBusy) {
		txBusy = true;
		USART2->CR1 |= USART_CR1_TXEIE;
	}
}

void USART2_IRQHandler() {
	if (USART2->SR & USART_SR_TXE) {
		if (txHead != txTail) {
			int primask = __get_PRIMASK();
			__disable_irq();
			USART2->DR = txBuffer[txTail];
			txTail = (txTail + 1) % BUFFER_SIZE;
			txCount--;
			__set_PRIMASK(primask);
		} else {
			USART2->CR1 &= ~USART_CR1_TXEIE;
			USART2->CR1 |= USART_CR1_TCIE;
		}
	}

	if (USART2->SR & USART_SR_TC) {
		USART2->CR1 &= ~USART_CR1_TCIE;
		txBusy = false;
	}
}

void USART_TransmitterInit() {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
	GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1);

	USART2->CR1 |= USART_CR1_UE;
	USART2->CR1 &= ~USART_CR1_M;
	USART2->CR1 &= ~USART_CR1_PCE;
	USART2->CR2 &= ~USART_CR2_STOP;
	USART2->BRR = 0x341;
	USART2->CR1 |= USART_CR1_TE;

	NVIC_EnableIRQ(USART2_IRQn);
}
