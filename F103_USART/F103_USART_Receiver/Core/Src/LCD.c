#include <LCD.h>

void delayMs(uint32_t ms) {
	ms /= 10;
	for (int i = 0; i < ms; i++) {
		for (int j = 0; j < 1400; j++) {
			__asm__("nop");
		}
	}
}

void LCD_WaitBusy() {
	GPIO_A_4_7_SetMode(Input);
	GPIOA->BSRR = RW_SET | RS_CLEAR; //read from control register
	uint32_t status;
	do {
		GPIOA->BSRR = EN_SET;
		delayMs(0);
		status = GPIOA->IDR;
		GPIOA->BSRR = EN_CLEAR;

		//!!!reading second nibble because even for reading, LCD driver excepts you to read both needles!!!
		GPIOA->BSRR = EN_SET;
		delayMs(0);
		GPIOA->BSRR = EN_CLEAR;
	} while (status & GPIO_IDR_IDR7);
	GPIO_A_4_7_SetMode(Output);
}

void LCD_NibbleWrite(enum PartialWriteMask mask, enum PartialWriteMode mode,
		char data) { //used for writing upper/lower bits of a command or data to the pins
	if (mode == COMMAND)
		GPIOA->BSRR = RS_CLEAR;
	else
		GPIOA->BSRR = RS_SET;
	GPIOA->BSRR = RW_CLEAR;

	GPIOA->ODR &= ~(GPIO_ODR_ODR4 | GPIO_ODR_ODR5 | GPIO_ODR_ODR6
			| GPIO_ODR_ODR7);
	if (mask == UPPER_4)
		GPIOA->ODR |= data & mask;
	else
		GPIOA->ODR |= (data & mask) << 4;

	GPIOA->BSRR = EN_SET;
	delayMs(0);
	GPIOA->BSRR = EN_CLEAR;
}

void LCD_Command(char command, bool checkBusyFlag) {
	if (checkBusyFlag)
		LCD_WaitBusy();
	LCD_NibbleWrite(UPPER_4, COMMAND, command);
	LCD_NibbleWrite(LOWER_4, COMMAND, command);
}

void LCD_Data(char data) {
	LCD_WaitBusy();
	LCD_NibbleWrite(UPPER_4, DATA, data);
	LCD_NibbleWrite(LOWER_4, DATA, data);
}

void LCD_Print(char *message, uint32_t size) {
	for (int i = 0; i < size; i++) {
		if (i == 16) LCD_Command(CURSOR_GO_TO_LINE_2, true);
		if (i == 32) {
			delayMs(1000);
			LCD_Command(CLEAR_DISPLAY, true);
			LCD_Command(CURSOR_RETURN_HOME, true);
		}
		LCD_Data(message[i]);
	}
}

void LCD_InitializeByInstruction() {
	//For understanding what is happening here, refer to 'Initializing by Instruction' section of the LCD datasheet.
	delayMs(41);
	LCD_NibbleWrite(UPPER_4, COMMAND, 0x30);
	delayMs(5);
	LCD_NibbleWrite(UPPER_4, COMMAND, 0x30);
	delayMs(1);
	LCD_NibbleWrite(UPPER_4, COMMAND, 0x30);
}

void LCD_Init() {
	GPIO_Init();
	LCD_InitializeByInstruction();

	LCD_NibbleWrite(UPPER_4, COMMAND, MODE_4BIT);
	delayMs(2);
	LCD_Command(MODE_4BIT_LINES_2_FONT_5X8, false);
	delayMs(2);
	LCD_Command(DISPLAY_OFF, false);
	delayMs(2);
//	LCD_Command(CLEAR_DISPLAY, false); //causes problem for some reason, but you have to do it according to Hitachi_HD44780 LCD datasheet
//	delayMs(2);
	LCD_Command(DISPLAY_ON_CURSOR_BLINKING, false);
	delayMs(2);

}
