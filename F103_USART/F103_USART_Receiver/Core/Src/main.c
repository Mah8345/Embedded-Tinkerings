#include <LCD.h>
#include <USART.h>


int main(){
	LCD_Init();
	USART_ReceiverInit();

	while(1){
		char received = USART_WaitChar();
		LCD_Data(received);
	}
}
