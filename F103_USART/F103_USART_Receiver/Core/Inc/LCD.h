#pragma once

#include <stdbool.h>
#include <GPIO.h>

#define RS_SET GPIO_BSRR_BS0
#define RW_SET GPIO_BSRR_BS1
#define EN_SET GPIO_BSRR_BS2
#define RS_CLEAR GPIO_BSRR_BR0
#define RW_CLEAR GPIO_BSRR_BR1
#define EN_CLEAR GPIO_BSRR_BR2

#define CLEAR_DISPLAY 0x01
#define CURSOR_RETURN_HOME 0x02
#define DISPLAY_OFF 0x08
#define DISPLAY_ON_CURSOR_BLINKING 0x0F
#define MOVE_CURSOR_RIGHT 0x06
#define MODE_4BIT 0x20
#define MODE_4BIT_LINES_2_FONT_5X8 0x28
#define CURSOR_GO_TO_LINE_2 0xC0

enum PartialWriteMask {
	LOWER_4 = 0x0F, UPPER_4 = 0xF0
};
enum PartialWriteMode {
	DATA,
	COMMAND
};

void delayMs(uint32_t time);
void LCD_WaitBusy(void);
void LCD_Init(void);
void LCD_NibbleWrite(enum PartialWriteMask mask, enum PartialWriteMode mode, char data);
void LCD_Command(char command, bool checkBusyFlag);
void LCD_Data(char data);
void LCD_Print(char *message, uint32_t length);
