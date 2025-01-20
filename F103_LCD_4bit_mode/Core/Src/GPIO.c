#include <GPIO.h>

void GPIO_A_4_7_SetMode(enum Mode mode) {
	if (mode == Output) {
		GPIOA->CRL |= (GPIO_CRL_MODE4_1 | GPIO_CRL_MODE5_1 | GPIO_CRL_MODE6_1
				| GPIO_CRL_MODE7_1);
	} else {
		GPIOA->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE6
				| GPIO_CRL_MODE7);
	}
}
void GPIO_A_0_2_SetOutputMode() {
	GPIOA->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_1 | GPIO_CRL_MODE2_1);
}

void GPIO_Init() {
	RCC->APB2ENR = RCC_APB2ENR_IOPAEN;
	GPIO_A_4_7_SetMode(Output);
	GPIO_A_0_2_SetOutputMode();
}
