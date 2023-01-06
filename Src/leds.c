#include <stdint.h>
#include "leds.h"
#include "board/timer.h"
#include "board/gpio.h"
#include "board/rcc.h"
#include "board/iser.h"
#include "board/adc.h"


//PB0 front right
//PB1 front left
//PB2 back right
//PB3 back left

void init_TIM3() {
	SET(RCC_APB1ENR1, TIM3EN); //TIM6x_CLK is enabled, running at 4MHz
	TIM3->EGR |= 1; //enable UIF to generate an interrupt
	TIM3->PSC = 1999; //Set Prescaler
	TIM3->CR1 &= ~(1 << 1); //OVF will generate an event

	// TIM3 Interrupt Initialization
	TIM3->ARR = 500;
	TIM3->SR = 0; //clear UIF if it is set
	TIM3->DIER |= 1;
	ISER1 |= 1 << 14; //enable global signaling for TIM6 interrupt

	TIM3->CR1 |= 1; //TIM6_CNT is enabled (clocked)

	enable_interrupts();
}

void init_leds() {
	SET(RCC_AHB2ENR, GPIOCEN);

	SET_BITS(GPIOC->MODER, 8 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOC->MODER, 9 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOC->MODER, 10 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOC->MODER, 11 * 2, OUTPUT_MODE, 2);

	init_TIM3();
}

static uint16_t blink_mask = 0;
void set_led_direction(led_direction d) {
	static uint16_t set_mask = 0;

	switch (d) {
	case LED_RIGHT:
		set_mask = 0;
		blink_mask = 0b0101;
		break;
	case LED_LEFT:
		set_mask = 0;
		blink_mask = 0b1010;
		break;
	case LED_FORWARD:
		set_mask = 0b0011;
		blink_mask = 0;
		break;
	case LED_BACK:
		set_mask = 0b1100;
		blink_mask = 0;
		break;
	case LED_STOP:
		blink_mask = 0;
		set_mask = 0;
		break;
	}
	GPIOC->BSRR = (0b1111 ^ blink_mask) << (8 + 0);
	GPIOC->BSRR = set_mask << (8 + 16);
}

static uint8_t even = 0;
void TIM3_IRQHandler(void) {
	GPIOC->BSRR = blink_mask << (8 + even);
	even = 16 - even;

	TIM3->SR = 0; //clear UIF
}

