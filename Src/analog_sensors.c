#include "board/adc.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"
#include "board/exti.h"
#include "drive.h"
#include "pins.h"

void init_sensors()
{
	ADC_shared->CCR |= (0b1011 << 18);
	// Enable Clock for GPIO
	SET(RCC_AHB2ENR, GPIOAEN);
	SET(RCC_AHB2ENR, GPIOCEN);

	// Enable Clock for ADC
	SET(RCC_AHB2ENR, ADCEN);

	// Select ADC clock as System clock
	RCC_CCIPR1 |= (3 << ADCSEL);
	//	 ADC_CCR &= ~(3 << 16);
	//	 ADC_CCR |= (1 << 17);

	// Change Pin Mode to Analog
	SET_BITS(JOY_PORT->MODER, JOY_VRx * 2, ANALOG_MODE, 2);
	SET_BITS(JOY_PORT->MODER, JOY_VRy * 2, ANALOG_MODE, 2);

	SET_BITS(LDR_PORT->MODER, LDR_R * 2, ANALOG_MODE, 2);
	SET_BITS(LDR_PORT->MODER, LDR_L * 2, ANALOG_MODE, 2);

	SET_BITS(JOY_PORT->PUPDR, JOY_VRx * 2, NOPULL, 2);
	SET_BITS(JOY_PORT->PUPDR, JOY_VRy * 2, NOPULL, 2);

	SET_BITS(LDR_PORT->PUPDR, LDR_R * 2, NOPULL, 2);
	SET_BITS(LDR_PORT->PUPDR, LDR_L * 2, NOPULL, 2);

	// Change Injected channel sequence length to 2 conversions
	SET_BITS(ADC1->JSQR, 0, 3, 4);

	// Add channels to sequence
	SET_BITS(ADC1->JSQR, 8, 5, 4);
	SET_BITS(ADC1->JSQR, 14, 6, 4);
	SET_BITS(ADC1->JSQR, 20, 1, 4);
	SET_BITS(ADC1->JSQR, 26, 2, 4);

	// Disable Deep-power-down for ADC
	ADC1->CR &= ~(1 << 29);

	// Enable ADC Voltage regulator
	SET(ADC1->CR, ADC_ADVREGEN);

	// Configure for Single conversion mode
	RESET(ADC1->CFGR, ADC_CONT);

	// Enable ADC
	SET(ADC1->CR, ADC_ADEN);

	// Wait ADC is enabled
	while (!(ADC1->ISR & 1))
		;

	// Enable interrupt for end of injected conversion
	SET(ADC1->IER, ADC_JEOSIE);
	SET(ISER1, 5);

	// Start regular conversion of ADC1
	SET(ADC1->CR, ADC_JADSTART);
}

static uint16_t joystick_x_calib = 0;
static uint16_t joystick_y_calib = 0;
static uint16_t joystick_y = 0;
static uint16_t joystick_x = 0;

static uint16_t LDR_right_calib = 0;
static uint16_t LDR_left_calib = 0;
static uint16_t ldr_direction = 0;

void refresh_sensors()
{
	uint16_t joystick_y_raw = ADC1->JDR1;
	uint16_t joystick_x_raw = ADC1->JDR2;

	if (joystick_x_calib < 1000)
	{
		joystick_y_calib = joystick_y_raw;
		joystick_x_calib = joystick_x_raw;
	}

	joystick_x = joystick_x_raw - joystick_x_calib;
	joystick_y = joystick_y_raw - joystick_y_calib;

	uint16_t LDR_right = ADC1->JDR3;
	uint16_t LDR_left = ADC1->JDR4;

	ldr_direction = ((LDR_left - LDR_left_calib) - (LDR_right - LDR_right_calib));
}

void ADC1_2_IRQHandler() {
	refresh_sensors();
	drive();
	SET(ADC1->ISR, ADC_JEOS);
}

void refresh_ldr_calib()
{
	LDR_right_calib = ADC1->JDR3;
	LDR_left_calib = ADC1->JDR4;
}

uint16_t get_joystick_x()
{
	return joystick_x;
}

uint16_t get_joystick_y()
{
	return joystick_y;
}

uint16_t get_ldr_direction()
{
	return ldr_direction;
}
