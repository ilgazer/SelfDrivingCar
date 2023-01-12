#include <stdint.h>
#include "drive.h"
#include "indicators.h"
#include "pins.h"
#include "utils.h"
#include "board/timer.h"
#include "board/gpio.h"
#include "board/rcc.h"
void init_indicators(){
	SET(RCC_AHB2ENR, GPIOAEN);
	SET(RCC_AHB2ENR, GPIOBEN);
	SET(RCC_AHB2ENR, GPIOCEN);

	SET_BITS(INDICATOR_STOP_PORT->MODER, INDICATOR_STOP_PIN * 2, OUTPUT_MODE, 2);
	SET_BITS(INDICATOR_AUTO_PORT->MODER, INDICATOR_AUTO_PIN * 2, OUTPUT_MODE, 2);
	SET_BITS(INDICATOR_OVERRIDE_PORT->MODER, INDICATOR_OVERRIDE_PIN * 2, OUTPUT_MODE, 2);


}

void set_indicators(uint8_t mode){
	static uint8_t previous_mode = 100;
	if(previous_mode == mode){
		return;
	}
	previous_mode = mode;
	if(mode <= HARD_STOP){
		INDICATOR_AUTO_PORT->ODR |= (1 << INDICATOR_AUTO_PIN);
	}else{
		INDICATOR_AUTO_PORT->ODR &= ~(1 << INDICATOR_AUTO_PIN);
	}
	if(mode == MANUAL_OVERRIDE){
		INDICATOR_OVERRIDE_PORT->ODR |= (1 << INDICATOR_OVERRIDE_PIN);
	}else{
		INDICATOR_OVERRIDE_PORT->ODR &= ~(1 << INDICATOR_OVERRIDE_PIN);
	}
	if(mode == HARD_STOP || mode == AUTO_STOP){
		INDICATOR_STOP_PORT->ODR |= (1 << INDICATOR_STOP_PIN);
	}else{
		INDICATOR_STOP_PORT->ODR &= ~(1 << INDICATOR_STOP_PIN);
	}
}
