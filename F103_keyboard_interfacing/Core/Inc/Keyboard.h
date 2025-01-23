#pragma once
#include <GPIO.h>
#include <stdbool.h>
#include <General.h>

#define COLUMNS_MSK 0xF0

bool Keyboard_KeyPressed();
char Keyboard_GetKey();
