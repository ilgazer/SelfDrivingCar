#include "buttons.h"

#include "board/timer.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"
#include "board/exti.h"

#include "pins.h"

void init_buttons() {
	SET(RCC_AHB2ENR, GPIOAEN);
	SET(RCC_AHB2ENR, GPIOCEN);

	SET_BITS(GPIOA->MODER, JOY_BTN * 2, INPUT_MODE, 2);
	SET_BITS(GPIOA->PUPDR, JOY_BTN * 2, PULLUP, 2);

	SET_BITS(GPIOC->MODER, BLUE_BTN * 2, INPUT_MODE, 2);
	SET_BITS(GPIOC->PUPDR, BLUE_BTN * 2, PULLDOWN, 2);

	EXTI->EXTISR[JOY_BTN] = 0;
	SET(EXTI->IMR1, JOY_BTN);
	SET(EXTI->FTSR1, JOY_BTN);
	SET(ISER0, 11 + JOY_BTN);

	EXTI->EXTISR[BLUE_BTN] = 2;
	SET(EXTI->IMR1, BLUE_BTN);
	SET(EXTI->RTSR1, BLUE_BTN);
	SET(ISER0, 11 + BLUE_BTN);
}

//Depends on the value of JOY_BTN
void EXTI6_IRQHandler() {
	joystick_button_handler();
	SET(EXTI->FPR1, JOY_BTN);
}

//Depends on the value of BLUE_BTN
void EXTI13_IRQHandler() {
	blue_button_handler();
	SET(EXTI->RPR1, BLUE_BTN);
}