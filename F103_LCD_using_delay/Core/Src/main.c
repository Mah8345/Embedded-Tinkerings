#include <stm32f103xb.h>
#include <LCD.h>


int main() {
	LCD_Init();

	char first[] = "Embedded";
	LCD_Print(first, sizeof(first)/sizeof(first[0]));

	LCD_Command(CURSOR_GO_TO_LINE_2);

	char second[] = "Tinkerings!";
	LCD_Print(second, sizeof(second)/sizeof(second[0]));


	while (1) {

	}
}
