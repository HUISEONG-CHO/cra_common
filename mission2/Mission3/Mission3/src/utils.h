#pragma once
#include "Car.h"
#include <string>

#define CLEAR_SCREEN "\033[H\033[2J"

void delay(int ms);
void printMenu(int step);
bool isValidInput(const char* endptr, int step, int answer);