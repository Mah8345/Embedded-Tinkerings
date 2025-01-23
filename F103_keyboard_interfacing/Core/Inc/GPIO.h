#pragma once
#include <stm32f103xb.h>

#define CRL_0_7_MSK 0xFFFFFFFF
#define CRL_0_3_MSK 0x0000FFFF
#define CRL_0_7_INPUT_PULL_UP_DOWN 0x88888888 //sets pins 0 to 7 to input pull-up/down (CNF and MODE)
#define CRL_0_3_INPUT_PULL_UP_DOWN 0x00008888
#define ODR_0_7_MSK 0xFF
#define ODR_0_3_MSK 0x0F
#define CRL_0_7_OUTPUT_PUSH_PULL_2MHz 0x66666666
#define CRL_0_3_OUTPUT_PUSH_PULL_2MHz 0x00006666

#define CRL_INPUT_PULL_UP_DOWN 0x8 //for setting only one pin to input pull-up/down mode
#define CRL_OUTPUT_PUSH_PULL_2MHz 0x6 //for setting only one pin to output push-pull 2MHz

enum Mode {
	INPUT_PULL_UP, OUTPUT, INPUT
};
enum GPIOB_Pin {
	PB0, PB1, PB2, PB3
};

void GPIO_A_0_7_SetMode(enum Mode mode);
void GPIO_A_8_10_SetAsOutput(void);

void GPIO_B_0_7_SetAsInputPullUp(void);
void GPIO_B_0_3_SetMode(enum Mode mode);

void GPIO_B_SetPinLow(enum GPIOB_Pin pin); //configures a row pin as output, then sets it low
void GPIO_B_SetPinAsInputPullUp(enum GPIOB_Pin pin); //configures a row pin as input pull-up

void GPIO_PortsInit(void);
