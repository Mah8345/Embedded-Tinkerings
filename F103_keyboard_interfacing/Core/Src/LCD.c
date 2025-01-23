#include <LCD.h>

void LCD_WaitBusy(){
	GPIO_A_0_7_SetMode(INPUT);
	GPIOA->BSRR = RS_CLEAR | RW_SET;

	uint32_t status;
	do {
		GPIOB->BSRR = EN_SET;
		delayMs(0);
		status = GPIOA->IDR;
		GPIOA->BSRR = EN_CLEAR;
	}
	while(status & GPIO_IDR_IDR7);//check D7

	GPIO_A_0_7_SetMode(OUTPUT);
}

void LCD_Command_NoCheck(unsigned char command) { //used only for the initialization
	GPIOA->ODR = command;
	GPIOA->BSRR = (RS_CLEAR | RW_CLEAR);

	GPIOA->BSRR = EN_SET;
	delayMs(0);
	GPIOA->BSRR = EN_CLEAR;

	delayMs(2);
}

void LCD_Command(unsigned char command){
	LCD_WaitBusy(); //wait until LCD is ready
	GPIOA->ODR = command;
	GPIOA->BSRR = (RS_CLEAR | RW_CLEAR);

	GPIOA->BSRR = EN_SET;
	delayMs(0);
	GPIOA->BSRR = EN_CLEAR;
}

void LCD_Data(char data) {
	LCD_WaitBusy(); //wait until LCD is ready
	GPIOA->ODR = data;
	GPIOA->BSRR = (RS_SET | RW_CLEAR);

	GPIOA->BSRR = EN_SET;
	delayMs(0);
	GPIOA->BSRR = EN_CLEAR;
}

void LCD_Print(char *message, uint32_t length){
	for (int i = 0; i < length; i++) {
		if (i == 32) {
			delayMs(1000);
			LCD_Command(CLEAR_DISPLAY);
			LCD_Command(CURSOR_RETURN_HOME);
		}
		if (i == 16) LCD_Command(CURSOR_GO_TO_LINE_2);
		LCD_Data(message[i]);
	}
}


void LCD_InitializationByCommand(){
	delayMs(45);
	LCD_Command_NoCheck(0x30);
	delayMs(5);
	LCD_Command_NoCheck(0x30);
	delayMs(1);
	LCD_Command_NoCheck(0x30);
}

void LCD_Init(){
	LCD_InitializationByCommand();


	LCD_Command_NoCheck(MODE_8_BIT);
	delayMs(2);
	LCD_Command_NoCheck(DISPLAY_ON);
	delayMs(2);
}

