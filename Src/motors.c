

#include <stdint.h>

#include "motors.h"
#include "utils.h"
#include "board/timer.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"

int speed = 0;
int direction = 0;
int is_stopped = 0;

//Motor driver pin mappings

//Port D
#define DRV_IN1 4
#define DRV_IN2 5
#define DRV_IN3 6
#define DRV_IN4 7

//Port A
#define DRV_ENA 2 //Left
#define DRV_ENB 3 //Right

//Motor definitions

#define MOTOR_FWD_L DRV_IN1
#define MOTOR_BCK_L DRV_IN2
#define MOTOR_SPD_L DRV_ENA

#define MOTOR_FWD_R DRV_IN3
#define MOTOR_BCK_R DRV_IN4
#define MOTOR_SPD_R DRV_ENB

typedef struct {
	uint32_t fwd_pin;
	uint32_t bck_pin;
	uint32_t spd_pin;
} Motor_t;

const Motor_t left_motor(DRV_IN1, DRV_IN2, DRV_ENA);


void init_motors(){
	SET(RCC_AHB2ENR, GPIOAEN);
	SET(RCC_AHB2ENR, GPIODEN);

	SET(RCC_APB2ENR, TIM15EN);

	SET_BITS(GPIOD->MODER, DRV_IN1 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOD->MODER, DRV_IN2 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOD->MODER, DRV_IN3 * 2, OUTPUT_MODE, 2);
	SET_BITS(GPIOD->MODER, DRV_IN4 * 2, OUTPUT_MODE, 2);


	SET_BITS(GPIOA->MODER, DRV_ENA * 2, ALTERNATE_MODE, 2);
	SET_BITS(GPIOA->AFR[0], DRV_ENA * 4, 14, 4);

	SET_BITS(GPIOA->MODER, DRV_ENB * 2, ALTERNATE_MODE, 2);
	SET_BITS(GPIOA->AFR[0], DRV_ENB * 4, 14, 4);
	TIM15->PSC = 4; //Set Prescalers
	TIM15->ARR = 4000; //Set ARR

	TIM15->SR = 0; //clear UIF if it is set

	TIM15->CCMR1 =
			CCx_OUTPUT << CC1S	|
			CCx_OUTPUT << CC2S	|
			OCxM_PWM1 << OC1M	|
			OCxM_PWM1 << OC2M	|
			1 << OC1PE			|
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

void update_motors(){
	if(is_stopped){
		SET();
	}
}


void set_speed(int speed){
	TIM15->CCR1 = 1000;
	TIM15->CCR2 = 2000;

	TIM15->SR = 0; //clear UIF if it is set
	TIM15->EGR |= 1;
}


void set_direction(int direction);

void stop(){

}

void enable();
