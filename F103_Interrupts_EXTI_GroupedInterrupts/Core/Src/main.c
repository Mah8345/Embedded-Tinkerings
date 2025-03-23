#include "main.h"

void dummyDelay(int time) {
	for (int i = 0; i < time; i++) {
		for (int j = 0; j < time; j++) {
			__asm__("nop");
		}
	}
}
//PA10 and PA11 are connected to different interrupt lines (EXTI10 and EXTI11 respectively)
//but they have the same ISR (EXTI15_10_IRQHandler), so you have to determine which pin the interrupt
//comes from in order to handle it properly
void EXTI15_10_IRQHandler() {
	if (EXTI->PR & EXTI_PR_PR10) {
		GPIOB->BSRR = GPIO_BSRR_BS8;
		EXTI->PR |= EXTI_PR_PR10;
	} else if (EXTI->PR & EXTI_PR_PR11) {
		GPIOB->BRR = GPIO_BRR_BR8;
		EXTI->PR |= EXTI_PR_PR11;
	}
}
void ConfigurePA10Interrupt() {
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
	GPIOA->CRH |= GPIO_CRH_CNF10_1; //pull-up/pull-down mode
	GPIOA->ODR |= GPIO_ODR_ODR10; //pull-up

	EXTI->FTSR |= EXTI_FTSR_FT10;
	EXTI->IMR |= EXTI_IMR_MR10;

	AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI10_Msk;

	NVIC_EnableIRQ(EXTI15_10_IRQn);
}
void ConfigurePA11Interrupt() {
	GPIOA->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
	GPIOA->CRH |= GPIO_CRH_CNF11_1; //pull-up/pull-down mode
	GPIOA->ODR |= GPIO_ODR_ODR11; //pull-up

	EXTI->FTSR |= EXTI_FTSR_FT11;
	EXTI->IMR |= EXTI_IMR_MR11;

	AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI11_Msk;
}

int main() {
	__disable_irq();
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8);
	GPIOB->CRH |= GPIO_CRH_MODE8_1;
	ConfigurePA10Interrupt();
	ConfigurePA11Interrupt();
	__enable_irq();
	while (1) {

	}
}
