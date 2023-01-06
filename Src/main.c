/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "board/timer.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"
#include "utils.h"
#include "motors.h"
#include "joystick.h"
#include "leds.h"
#include "board/adc.h"
void ADC1_2_IRQHandler() {

	uint32_t joystick_y = ADC1->DR;
	uint32_t joystick_x = ADC1->DR;

	if(joystick_y < 4096 / 3){
		set_led_direction(led_left);
	}else if(joystick_y  > 8192 / 3){
		set_led_direction(led_right);
	}else if(joystick_x < 4096 / 3){
		set_led_direction(led_forward);
	}else if(joystick_x > 8192 / 3){
		set_led_direction(led_back);
	}



}

int main(void) {
//	init_motors();
//	set_speed(1200);
	init_leds();
	set_led_direction(led_left);
	initialize_adc();
	while(1){

	}
}
