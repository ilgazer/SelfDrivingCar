

#ifndef DRIVE
#define DRIVE

#define MANUAL 1
#define MANUAL_OVERRIDE 2
#define HARD_STOP 3
#define AUTO_STOP 4
#define AUTO_WAIT 5
#define AUTO 7
#include "board/adc.h"
#include "leds.h"
#include "motors.h"

#include <stdint.h>

void set_mode(uint8_t mode);
void init_mode(uint8_t mode);
void drive();
void driver_stop();
#endif
