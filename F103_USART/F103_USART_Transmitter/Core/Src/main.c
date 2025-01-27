#include <USART.h>

void delay(int time) {
	for (int i = 0; i < time; i++) {
		for (int j = 0; j < 100; j++) {
			__asm__("nop");
		}
	}
}

int main() {
	USART_TransmitterInit();

	delay(2500); //delay to allow initialization of both receiver and transmitter

	char message[] = "Hello from USART!";
	uint32_t length = sizeof(message)/sizeof(message[0]);
	USART_SendMessage(message, length);

	while (1) {

	}
}
