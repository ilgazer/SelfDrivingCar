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
#include "board/exti.h"

#include "utils.h"
#include "motors.h"
#include "analog_sensors.h"
#include "leds.h"
#include "drive.h"
#include "pins.h"
#include "indicators.h"
#include "ultrasonic.h"
#include "buttons.h"

#define BUSY_WAIT 1

void init_TIM7() {
	SET(RCC_APB1ENR1, TIM7EN); //TIM6x_CLK is enabled, running at 4MHz
	TIM7->EGR |= 1; //enable UIF to generate an interrupt
	TIM7->PSC = 15999; //Set Prescaler
	TIM7->CR1 &= ~(1 << 1); //OVF will generate an event

	// TIM6 Interrupt Initialization
	TIM7->ARR = 2;
	TIM7->SR = 0; //clear UIF if it is set
	TIM7->DIER |= 1;
	ISER1 |= 1 << 18; //enable global signaling for TIM6 interrupt

	TIM7->CR1 |= 1; //TIM6_CNT is enabled (clocked)

	enable_interrupts();
}

void TIM7_IRQHandler(void) {
	SET(ADC1->CR, ADC_JADSTART);
	TIM7->SR = 0; //clear UIF
}

int main(void) {
	init_drive(MANUAL);
	init_indicators();
	init_motors();
	init_leds();
	set_led_direction(LED_STOP);
	init_sensors();
	init_ultrasonic();
	init_buttons();
	if (BUSY_WAIT) {
		while (1) {
			for (int i = 0; i < 33300 / 2; i++)
				;
			SET(ADC1->CR, ADC_JADSTART);
		}
	} else {
		init_TIM7();
		while (1) {
			asm volatile("wfi");
		}
	}
}

