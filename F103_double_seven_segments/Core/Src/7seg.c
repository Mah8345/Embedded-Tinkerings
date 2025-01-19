#include <7seg.h>

//masks for common anode 7-segment
const uint32_t SevenSegMasks[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};

void delay(uint32_t time){
	for (int i = 0;i<time;i++){
		for (int j = 0;j<time;j++){
			__asm__("nop");
		}
	}
}
void SevenSeg_DisplayDecimal(uint32_t decimalNumber){
	if (decimalNumber > 99 || decimalNumber < 0) return;


	uint32_t ones = decimalNumber % 10;
	uint32_t tens = decimalNumber / 10;

	//displaying tens
	GPIOB->BSRR = GPIO_BSRR_BR1;
	GPIOB->BSRR = GPIO_BSRR_BS0;
	GPIOA->ODR = SevenSegMasks[tens];

	delay(50);

	//displaying ones
	GPIOB->BSRR = GPIO_BSRR_BR0;
	GPIOB->BSRR = GPIO_BSRR_BS1;
	GPIOA->ODR = SevenSegMasks[ones];

	delay(50);
}


void SevenSeg_DisplayFloat(float floatNumber){
	if (floatNumber < 0 || floatNumber > 99) return;

	uint32_t integerPart = (uint32_t) floatNumber;

	if (integerPart > 9) return;

	uint32_t fractionalPart = (uint32_t) (10 * (floatNumber - integerPart));

	//displaying integer part
	GPIOB->BSRR = GPIO_BSRR_BR1;
	GPIOB->BSRR = GPIO_BSRR_BS0;
	GPIOA->ODR = SevenSegMasks[integerPart] & ~GPIO_ODR_ODR0; //clearing PA0 to display DP


	delay(50);


	//displaying fractional part
	GPIOB->BSRR = GPIO_BSRR_BR0;
	GPIOB->BSRR = GPIO_BSRR_BS1;
	GPIOA->ODR = SevenSegMasks[fractionalPart];

	delay(50);
}
