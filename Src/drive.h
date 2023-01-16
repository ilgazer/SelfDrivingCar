

#ifndef DRIVE
#define DRIVE

#define MANUAL 1
#define MANUAL_OVERRIDE 2
#define MANUAL_STOP 3
#define AUTO_STOP 4
#define AUTO_WAIT 5
#define AUTO 7
#include "board/adc.h"
#include "leds.h"
#include "motors.h"

#include <stdint.h>

void set_mode(uint8_t mode);
void init_drive(uint8_t mode);
void drive();
void driver_stop();
void joystick_button_handler();
void blue_button_handler();
uint8_t get_mode();
#endif
