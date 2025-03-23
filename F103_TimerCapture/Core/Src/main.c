#include <stm32f103xb.h>
#include <USART.h>
#include <stdio.h>

void TIM2_Init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
	GPIOA->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_CNF0_1);

	TIM2->PSC = 8000 - 1;
	TIM2->ARR = 1000 - 1;

	TIM2->CNT = 0;
	TIM2->CCR1 = 0;

	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM2->CCMR1 |= (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1); //010000 100000 110000

	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM3_Init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; //enabling clock to the timer

	//configuring PA6(timer 3 channel 1) as alternate function:
	GPIOA->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6);
	GPIOA->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_CNF6_1);

	TIM3->PSC = (8000 - 1);

	//configuring timer as input capture mode
	TIM3->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;

	TIM3->CCER &= ~TIM_CCER_CC1P; //capture at rising-edge
	TIM3->CCER |= TIM_CCER_CC1E; //enable compare/capture mode

	TIM3->ARR = 65535;
	TIM3->CNT = 0;

	TIM3->CR1 |= TIM_CR1_CEN;
}

int main() {
	TIM2_Init();
	TIM3_Init();
	USART_TransmitterInit();

	int lastCapturedValue = 0;
	int currentCapturedValue = 0;

	while (1) {
		if (TIM3->SR & TIM_SR_CC1IF) {
			//print pulse width
			currentCapturedValue = TIM3->CCR1;
			char message[20];
			int size = sizeof(message) / sizeof(message[0]);
			float pulseWidth = (currentCapturedValue - lastCapturedValue)
					/ 1000;
			int pulseWidthMantissa = (int) pulseWidth;
			int pulseWidthFraction = (int) ((pulseWidth - pulseWidthMantissa + 1.0f) * 100);

			sprintf(message, "%d \r\n", (currentCapturedValue - lastCapturedValue));

			lastCapturedValue = currentCapturedValue;


			USART_SendMessage(message, size);
			TIM3->SR &= ~TIM_SR_CC1IF;
		}
	}
}
