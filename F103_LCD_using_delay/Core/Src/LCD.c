#include <LCD.h>




void delayMs(uint32_t ms) { //approximately ms delay, no calculations for the numbers, they are experimental
	ms/=10;
	for (int i = 0; i < ms; i++) {
		for (int j = 0; j < 1400; j++) {
			__asm__("nop");
		}
	}
}

void Ports_Init(){
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);//enabling ports A,B clock

	//PA0-PA7 for D0-D7
	GPIOA->CRL |= (GPIO_CRL_MODE0_1
			| GPIO_CRL_MODE1_1
			| GPIO_CRL_MODE2_1
			| GPIO_CRL_MODE3_1
			| GPIO_CRL_MODE4_1
			| GPIO_CRL_MODE5_1
			| GPIO_CRL_MODE6_1
			| GPIO_CRL_MODE7_1
	);

	//PB0-PB2 for RS,RW,EN
	GPIOB->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_1 | GPIO_CRL_MODE2_1);
	GPIOB->BSRR = EN_CLEAR | RW_CLEAR;
}

void LCD_Command(unsigned char command) {
	GPIOA->ODR = command;
	GPIOB->BSRR = (RS_CLEAR | RW_CLEAR);

	GPIOB->BSRR = EN_SET;
	delayMs(0);
	GPIOB->BSRR = EN_CLEAR;

	delayMs(2);
}


void LCD_InitializationByCommand(){
	delayMs(40);
	LCD_Command(0x30);
	delayMs(10);
	LCD_Command(0x30);
	delayMs(1);
	LCD_Command(0x30);
}

void LCD_Init(){
	Ports_Init();
	LCD_InitializationByCommand();


	LCD_Command(MODE_8_BIT);
	LCD_Command(DISPLAY_ON);
}

void LCD_Data(char data) {

	GPIOB->BSRR = (RS_SET | RW_CLEAR);
	GPIOA->ODR = data;

	GPIOB->BSRR = EN_SET;
	delayMs(0);
	GPIOB->BSRR = EN_CLEAR;

	delayMs(2);
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
