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

static const uint16_t blink_vals[] = {0, 0, 0, 0b0101, 0b1010};
static const uint16_t set_vals[] = {0,0b0011, 0b1100, 0, 0};

static uint8_t even = 0;

static led_direction prev_led_direction = LED_STOP;
static uint16_t blink_val = 0;
void set_led_direction(led_direction d) {
	if (d != prev_led_direction) {
		prev_led_direction = d;

		TIM3->CNT = 0;

		GPIOC->BSRR = 0b1111 << 8;
		GPIOC->BSRR = set_vals[d] << (8 + 16);
		blink_val = blink_vals[d];

		even = 16;
		TIM3->CNT = TIM3->ARR - 2;
	}
}

void TIM3_IRQHandler(void) {
	GPIOC->BSRR = blink_val << (8 + even);
	even = 16 - even;

	TIM3->SR = 0; //clear UIF
}

