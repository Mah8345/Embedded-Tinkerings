#include <stm32f103xb.h>

//masks for common anode 7-segment
const uint8_t seven_seg_masks[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};

void SevenSeg_display_digit(uint32_t digit){
	if (digit < 0 || digit > 9) return;

	GPIOA->BSRR = GPIO_BSRR_BS0; //setting enable bit
	GPIOB->ODR = seven_seg_masks[digit]; //setting ODR according to mask
}

int main(){
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN); //clock activation for A,B ports

	GPIOB->CRL |= (GPIO_CRL_MODE0_1
			| GPIO_CRL_MODE1_1
			| GPIO_CRL_MODE2_1
			| GPIO_CRL_MODE3_1
			| GPIO_CRL_MODE4_1
			| GPIO_CRL_MODE5_1
			| GPIO_CRL_MODE6_1
			| GPIO_CRL_MODE7_1
	); //PB0 to PB7 for LED pins

	GPIOA->CRL |= GPIO_CRL_MODE0_1; //PA0 for enable pin

	SevenSeg_display_digit(6);
	while (1){

	}
}
