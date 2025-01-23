#include <GPIO.h>

//LCD GPIO functions
void GPIO_A_0_7_SetMode(enum Mode mode) {
	GPIOA->CRL &= ~CRL_0_7_MSK;
	if (mode == INPUT_PULL_UP) {
		GPIOA->CRL |= CRL_0_7_INPUT_PULL_UP_DOWN;
		GPIOA->ODR = ODR_0_7_MSK;
	} else {
		GPIOA->CRL |= CRL_0_7_OUTPUT_PUSH_PULL_2MHz;
	}
}

void GPIO_A_8_10_SetAsOutput(void) {
	GPIOA->CRH |= (GPIO_CRH_MODE8_1 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE10_1);
}

//keyboard GPIO functions
void GPIO_B_0_7_SetAsInputPullUp(void) {
	GPIOB->CRL &= ~CRL_0_7_MSK;
	GPIOB->CRL |= CRL_0_7_INPUT_PULL_UP_DOWN;
	GPIOB->ODR |= ODR_0_7_MSK; //enable pull-up for pins 0-7
}

void GPIO_B_0_3_SetMode(enum Mode mode) {
	if (mode == OUTPUT) {
		GPIOB->CRL &= ~CRL_0_3_MSK;
		GPIOB->CRL |= CRL_0_3_OUTPUT_PUSH_PULL_2MHz;
	} else if(mode == INPUT_PULL_UP) {
		GPIOB->CRL &= ~CRL_0_3_MSK;
		GPIOB->CRL |= CRL_0_3_INPUT_PULL_UP_DOWN;
		GPIOB->ODR |= ODR_0_3_MSK; //enable pull-up for pins 0-3
	} else {
		GPIOB->CRL &= ~CRL_0_3_MSK;
		GPIOB->CRL |= 0x4;
	}
}

void GPIO_B_SetPinLow(enum GPIOB_Pin pin) {
	GPIOB->CRL &= ~(0xF << (pin * 4)); //clear 4 bits (CNF + MODE) of the corresponding pin
	GPIOB->CRL |= CRL_OUTPUT_PUSH_PULL_2MHz << (pin * 4);
	GPIOB->BRR = 1 << pin;
}

void GPIO_B_SetPinAsInputPullUp(enum GPIOB_Pin pin) {
	GPIOB->BSRR = 1 << pin; //set ODR bit of the corresponding pin to 1 to enable pull-up
	GPIOB->CRL &= ~(0xF << (pin * 4));
	GPIOB->CRL |= CRL_INPUT_PULL_UP_DOWN << (pin * 4);
}

//initialization
void GPIO_PortsInit(void) {
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);

	//LCD related pins
	GPIO_A_0_7_SetMode(OUTPUT);
	GPIO_A_8_10_SetAsOutput();

	//Keyboard related pins
	GPIO_B_0_7_SetAsInputPullUp();
}
