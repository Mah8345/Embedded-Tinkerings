#include <main.h>

void dummyDelay(int time) {
	for (int i = 0; i < time; i++) {
		for (int j = 0; j < time; j++) {
			__asm__("nop");
		}
	}
}
void EXTI0_IRQHandler() {
	GPIOB->BSRR = GPIO_BSRR_BS8;
	dummyDelay(500);
	GPIOB->BSRR = GPIO_BSRR_BR8;
	dummyDelay(500);
	GPIOB->BSRR = GPIO_BSRR_BS8;
	dummyDelay(500);
	GPIOB->BSRR = GPIO_BSRR_BR8;
	EXTI->PR |= EXTI_PR_PR0;
}

void ConfigurePA0Interrupt() {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

	GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0); //enable input mode
	GPIOA->CRL |= GPIO_CRL_CNF0_1; //enable pull-up/down mode
	GPIOA->ODR |= GPIO_ODR_ODR0; //enable pull-up

	EXTI->FTSR |= EXTI_FTSR_FT0; //trigger on falling-edge
	EXTI->IMR |= EXTI_IMR_MR0; //unmask the EXTI0 interrupts

	AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0_Msk);
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PA; //not necessary as PA's corresponding bits for this is 0000, but you would do it for other pins like PB

	NVIC_EnableIRQ(EXTI0_IRQn); //enabling the interrupt at NVIC
}
int main() {
	__disable_irq(); //disable interrupts globally before interrupt configurations
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
	GPIOB->CRH |= GPIO_CRH_MODE8_1;
	GPIOB->BRR = GPIO_BRR_BR8;

	ConfigurePA0Interrupt();
	__enable_irq();

	while (1) {

	}
}
