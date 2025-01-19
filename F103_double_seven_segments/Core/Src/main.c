#include <stm32f103xb.h>
#include <7seg.h>

int main() {
	RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPBEN);//enabling clock for A,B ports
	GPIOA->CRL |= (GPIO_CRL_MODE0_1
			| GPIO_CRL_MODE1_1
			| GPIO_CRL_MODE2_1
			| GPIO_CRL_MODE3_1
			| GPIO_CRL_MODE4_1
			| GPIO_CRL_MODE5_1
			| GPIO_CRL_MODE6_1
			| GPIO_CRL_MODE7_1
	);//PA0 to PA7 for input pins

	GPIOB->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_1);//PB0 and PB1 for tens and ones enables
	while(1) {
		SevenSeg_DisplayDecimal(21);
	}
}
