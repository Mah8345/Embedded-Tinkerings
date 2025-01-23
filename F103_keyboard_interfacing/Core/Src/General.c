#include <General.h>

void delayMs(uint32_t ms) { //approximately ms delay, no calculations for the numbers, they are experimental
	ms/=10;
	for (int i = 0; i < ms; i++) {
		for (int j = 0; j < 1400; j++) {
			__asm__("nop");
		}
	}
}
