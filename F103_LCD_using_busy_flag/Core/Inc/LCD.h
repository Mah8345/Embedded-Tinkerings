#pragma once

#include <stm32f103xb.h>
#include <GPIO.h>

#define RS_SET GPIO_BSRR_BS0
#define RW_SET GPIO_BSRR_BS1
#define EN_SET GPIO_BSRR_BS2
#define RS_CLEAR GPIO_BSRR_BR0
#define RW_CLEAR GPIO_BSRR_BR1
#define EN_CLEAR GPIO_BSRR_BR2

#define CLEAR_DISPLAY 0x01
#define CURSOR_RETURN_HOME 0x02
#define DISPLAY_ON 0x0F
#define MODE_8_BIT 0x38
#define CURSOR_GO_TO_LINE_2 0xC0

void delayMs(uint32_t time);
void LCD_WaitBusy(void);
void LCD_Init(void);
void LCD_Command(unsigned char command);
void LCD_Data(char data);
void LCD_Print(char *message, uint32_t length);
