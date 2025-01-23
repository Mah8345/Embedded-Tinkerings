#include <Keyboard.h>

const char keys[4][4] = {
		{ '7', '8', '9', '/' },
		{ '4', '5', '6', '*' },
		{ '1', '2', '3', '-' },
		{ 'C', '0', '=', '+' }
};

void Keyboard_SetRowsLow() {
	GPIO_B_0_3_SetMode(OUTPUT);
	GPIOB->ODR &= ~(ODR_0_3_MSK);
}

bool Keyboard_KeyPressed() {
	Keyboard_SetRowsLow();
	delayMs(0);
	uint32_t column = GPIOB->IDR & COLUMNS_MSK;
	GPIO_B_0_3_SetMode(INPUT_PULL_UP);
	if ( column != COLUMNS_MSK) //if any column is 0, then a key is pressed
		return true;
	return false;
}

uint32_t Keyboard_GetColumn(uint32_t column_msk) {
	//you have to find the column based on its mask to return the corresponding key
	column_msk >>= 4;//move columns to first four bit positions
	for (int i = 0; i < 4; i++) {
		if ((column_msk & (1 << i)) == 0)
			return i;
	}
	return -1;
}

bool state = 0;
char Keyboard_GetKey() {
	if (Keyboard_KeyPressed()) {
		//set rows LOW one by one and check if any button is pressed at the row (column != 0xF)
		for(int row = 0; row < 4; row++){
			GPIO_B_SetPinLow(row);
			delayMs(0);
			uint32_t column_bit_map = (GPIOB->IDR & COLUMNS_MSK);
			GPIO_B_SetPinAsInputPullUp(row); //set pin back to input high to avoid short circuiting pins
			if (column_bit_map != COLUMNS_MSK){
				uint32_t column = Keyboard_GetColumn(column_bit_map);
				return keys[row][column];
			}
		}
	}
	return 0;
}

/*
 * if (column != -1){
					RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
					GPIOC->CRH |= GPIO_CRH_MODE13_1;
					if(!state) GPIOC->ODR |= GPIO_ODR_ODR13;
					else GPIOC->ODR &= ~GPIO_ODR_ODR13;
				}*/
