#pragma once

#include <stm32f103xb.h>
#include <GPIO.h>
#include <General.h>

#define RS_SET GPIO_BSRR_BS8
#define RW_SET GPIO_BSRR_BS9
#define EN_SET GPIO_BSRR_BS10
#define RS_CLEAR GPIO_BSRR_BR8
#define RW_CLEAR GPIO_BSRR_BR9
#define EN_CLEAR GPIO_BSRR_BR10

#define CLEAR_DISPLAY 0x01
#define CURSOR_RETURN_HOME 0x02
#define DISPLAY_ON 0x0F
#define MODE_8_BIT 0x38
#define CURSOR_GO_TO_LINE_2 0xC0

void LCD_WaitBusy(void);
void LCD_Init(void);
void LCD_Command(unsigned char command);
void LCD_Data(char data);
void LCD_Print(char *message, uint32_t length);
