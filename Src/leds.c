#include <stdint.h>
#include "leds.h"
#include "board/timer.h"
#include "board/gpio.h"
#include "board/rcc.h"
#include "board/iser.h"
#include "board/adc.h"

//PE12 front right
//PE13 front left
//PE14 back right
//PE15 back left

void init_TIM6() {
	SET(RCC_APB1ENR1, TIM6EN); //TIM6x_CLK is enabled, running at 4MHz
	TIM6->EGR |= 1; //enable UIF to generate an interrupt
	TIM6->PSC = 15999; //Set Prescaler
	TIM6->CR1 &= ~(1 << 1); //OVF will generate an event

	// TIM6 Interrupt Initialization
	TIM6->ARR = 125;
	TIM6->SR = 0; //clear UIF if it is set
	TIM6->DIER |= 1;
	ISER1 |= 1 << 17; //enable global signaling for TIM6 interrupt

	TIM6->CR1 |= 1; //TIM6_CNT is enabled (clocked)

	enable_interrupts();
}

void init_leds() {
	SET(RCC_AHB2ENR, GPIOEEN);

	SET_BITS(GPIOE->MODER, 12 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOE->MODER, 13 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOE->MODER, 14 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOE->MODER, 15 * 2, OUTPUT_MODE, 2);

	init_TIM6();
}

static const uint16_t blink_vals[] = {0, 0, 0, 0b1010, 0b0101};
static const uint16_t set_vals[] = {0,0b1100, 0b0011, 0, 0};

static uint8_t even = 0;

static led_direction prev_led_direction = -1;
static uint16_t blink_val = 0;
void set_led_direction(led_direction d) {
	if (d != prev_led_direction) {
		prev_led_direction = d;

		TIM6->CNT = 0;

		GPIOE->BSRR = 0b1111 << (12 + 16);
		GPIOE->BSRR = set_vals[d] << 12;
		blink_val = blink_vals[d];

		even = 16;
		TIM6->CNT = TIM6->ARR - 2;
	}
}

void TIM6_IRQHandler(void) {
	GPIOE->BSRR = blink_val << (12 + even);
	even = 16 - even;

	TIM6->SR = 0; //clear UIF
}

