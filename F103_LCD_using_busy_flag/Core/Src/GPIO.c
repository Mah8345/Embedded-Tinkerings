#include <GPIO.h>


void GPIO_PortsInit(){
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);
	GPIO_A_0_7_SetMode(Output);
	GPIO_B_0_2_SetMode(Output);
}

void GPIO_A_0_7_SetMode(enum Mode mode) {
	if (mode == Input) {
		GPIOA->CRL &= ~(GPIO_CRL_MODE0 |
		GPIO_CRL_MODE1 |
		GPIO_CRL_MODE2 |
		GPIO_CRL_MODE3 |
		GPIO_CRL_MODE4 |
		GPIO_CRL_MODE5 |
		GPIO_CRL_MODE6 |
		GPIO_CRL_MODE7);
	} else {
		GPIOA->CRL |= ( GPIO_CRL_MODE0_1 |
		GPIO_CRL_MODE1_1 |
		GPIO_CRL_MODE2_1 |
		GPIO_CRL_MODE3_1 |
		GPIO_CRL_MODE4_1 |
		GPIO_CRL_MODE5_1 |
		GPIO_CRL_MODE6_1 |
		GPIO_CRL_MODE7_1);
	}
}

void GPIO_B_0_2_SetMode(enum Mode mode) {
	if (mode == Input) {
		GPIOB->CRL &= ~(GPIO_CRL_MODE0 |
		GPIO_CRL_MODE1 |
		GPIO_CRL_MODE2);
	} else {
		GPIOB->CRL |= ( GPIO_CRL_MODE0_1 |
		GPIO_CRL_MODE1_1 |
		GPIO_CRL_MODE2_1);
	}
}
