

#ifndef DRIVE
#define DRIVE

#define AUTO 0
#define MANUAL 1
#define MANUAL_OVERRIDE 2
#define HARD_STOP 3

#include <stdint.h>

void set_mode(uint8_t mode);
void drive();

#endif
