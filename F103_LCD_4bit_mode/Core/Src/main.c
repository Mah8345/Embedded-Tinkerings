#include <stm32f103xb.h>
#include <LCD.h>

int main(){
	LCD_Init();

	char message[] = "Embedded Tinkerings!";
	LCD_Print(message, sizeof(message)/sizeof(message[0]));
	while(1){

	}
}
