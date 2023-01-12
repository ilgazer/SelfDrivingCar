
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "motors.h"
#include "utils.h"
#include "pins.h"
#include "board/timer.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"

int _motors_speed = 0;
int _motors_direction = 0;
int _motors_is_stopped = 0;

typedef struct {
	volatile uint32_t *speed;
	uint32_t dir_pin_fwd;
	uint32_t dir_pin_back;

} Motor_t;

const Motor_t right_motor = {&(TIM15->CCR1), DRV_IN2,  DRV_IN1};
const Motor_t left_motor = {&(TIM15->CCR2), DRV_IN4,  DRV_IN3};

void init_motors() {
	SET(RCC_AHB2ENR, GPIOAEN);
	SET(RCC_AHB2ENR, GPIOCEN);

	SET(RCC_APB2ENR, TIM15EN);

	SET_BITS(DRV_PORT->MODER, DRV_IN1 * 2, OUTPUT_MODE, 2);
	SET_BITS(DRV_PORT->MODER, DRV_IN2 * 2, OUTPUT_MODE, 2);
	SET_BITS(DRV_PORT->MODER, DRV_IN3 * 2, OUTPUT_MODE, 2);
	SET_BITS(DRV_PORT->MODER, DRV_IN4 * 2, OUTPUT_MODE, 2);

	SET_BITS(DRV_EN_PORT->MODER, DRV_ENA * 2, ALTERNATE_MODE, 2);
	SET_BITS(DRV_EN_PORT->AFR[0], DRV_ENA * 4, 14, 4);

	SET_BITS(DRV_EN_PORT->MODER, DRV_ENB * 2, ALTERNATE_MODE, 2);
	SET_BITS(DRV_EN_PORT->AFR[0], DRV_ENB * 4, 14, 4);
	TIM15->PSC = 4; //Set Prescalers
	TIM15->ARR = 4000; //Set ARR

	TIM15->SR = 0; //clear UIF if it is set

	TIM15->CCMR1 =
			CCx_OUTPUT << CC1S |
			CCx_OUTPUT << CC2S |
			OCxM_PWM1 << OC1M |
			OCxM_PWM1 << OC2M |
			1 << OC1PE |
			1 << OC2PE;

	SET(TIM15->CR1, ARPE);

	TIM15->BDTR |= 1 << 15;

	TIM15->SR = 0; //clear UIF if it is set
	TIM15->EGR |= 1;

	SET(TIM15->CCER, CC1E);
	SET(TIM15->CCER, CC2E);

	SET(TIM15->CR1, CEN); //TIMx_CNT is enabled (clocked)

	TIM15->SR = 0; //clear UIF if it is set
	TIM15->EGR |= 1;
}

static uint32_t gpiocodr;
void set_motor(Motor_t motor, int apply_brake, int value) {
	if (apply_brake) {
		SET_BIT(DRV_PORT->ODR, motor.dir_pin_fwd, 0);
		SET_BIT(DRV_PORT->ODR, motor.dir_pin_back, 0);
		*motor.speed = 0xffff;
	} else {
		SET_BIT(DRV_PORT->ODR, motor.dir_pin_fwd, value >= 0 ? 1 : 0);
		SET_BIT(DRV_PORT->ODR, motor.dir_pin_back, value < 0 ? 1 : 0);
		*motor.speed = abs(value);
	}
	gpiocodr = (GPIOC->ODR >> 9) & 0b1111;
}

void update_motors() {
	set_motor(left_motor, _motors_is_stopped, _motors_speed + _motors_direction);
	set_motor(right_motor, _motors_is_stopped, _motors_speed - _motors_direction);
}


void set_speed(int speed) {
	_motors_speed = speed;
	update_motors();
}

void set_direction(int direction){
	_motors_direction = direction;
	update_motors();
}

void stop() {
	_motors_is_stopped = 1;
	update_motors();
}

void enable(){
	_motors_is_stopped = 0;
	update_motors();
}
