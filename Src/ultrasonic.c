
#include <stdint.h>
#include <math.h>

#include "ultrasonic.h"
#include "motors.h"
#include "utils.h"
#include "board/timer.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"


void init_ultrasonic() {
	SET(RCC_AHB2ENR, GPIOEEN);
	SET(RCC_APB1ENR1, TIM3EN);


	SET_BITS(GPIOE->MODER, 3 * 2, ALTERNATE_MODE, 2);
	SET_BITS(GPIOE->AFR[0], 3 * 4, 2, 4);

	SET_BITS(GPIOE->MODER, 5 * 2, ALTERNATE_MODE, 2);
	SET_BITS(GPIOE->AFR[0], 5 * 4, 2, 4);

	TIM3->PSC = 4; //Set Prescalers
	TIM3->ARR = 60000; //Set ARR

	RESET(TIM3->CR1, UDIS);
	TIM3->SR = 0; //clear UIF if it is set

	TIM3->CCMR1 =
			CCx_OUTPUT << CC1S |
			OCxM_PWM1 << OC1M |
			1 << OC1PE;

	TIM3->CCMR2 =
			0b01 << CC3S |
			0b10 << CC4S;

	TIM3->CCR1 = 10;

	SET(TIM3->CR1, ARPE);

	TIM3->BDTR |= 1 << 15;

	TIM3->SR = 0; //clear UIF if it is set
	TIM3->EGR |= 1;


	SET(TIM3->DIER, CC4IE);
	SET(ISER1, 46 - 32); //enable global signaling for TIMx interrupt

	TIM3->CCER =
			1 << CC4P |
			1 << CC1E |
			1 << CC3E |
			1 << CC4E;

	SET(TIM3->CR1, CEN); //TIMx_CNT is enabled (clocked)

	TIM3->SR = 0; //clear UIF if it is set
	TIM3->EGR |= 1;
}

static int ultrasonic_distance =1000;
void TIM3_IRQHandler(void) {
	ultrasonic_distance = (TIM3->CCR4 - TIM3->CCR3) / 58;

	TIM3->SR = 0; //clear UIF
}

int get_distance(){
	return ultrasonic_distance;
}



