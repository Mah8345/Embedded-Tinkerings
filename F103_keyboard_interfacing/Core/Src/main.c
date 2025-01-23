#include <GPIO.h>
#include <LCD.h>
#include <Keyboard.h>


int main(){
	GPIO_PortsInit();
	LCD_Init();
	while(1){
		char key = Keyboard_GetKey();
		if (key != 0){
			if (key == 'C'){
				LCD_Command(CLEAR_DISPLAY);
				LCD_Command(CURSOR_RETURN_HOME);
			}
			LCD_Data(key);
			delayMs(400); //debouncing delay
		}
	}
}
