#include "board/adc.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"
#include "board/exti.h"


//PA0, PA1 joystick inputs
//PE15 push button interrupt
void initialize_adc() {
	ADC_shared->CCR |= (0b1011 << 18);
	//Enable Clock for GPIO
	SET(RCC_AHB2ENR, GPIOAEN);

	//Enable Clock for ADC
	SET(RCC_AHB2ENR, ADCEN);

	//Select ADC clock as System clock
	RCC_CCIPR1 |= (3 << ADCSEL);
	//	 ADC_CCR &= ~(3 << 16);
	//	 ADC_CCR |= (1 << 17);

	//Change Pin Mode to Analog
	SET_BITS(GPIOA->MODER, 0 * 2, ANALOG_MODE, 2);
	SET_BITS(GPIOA->MODER, 1 * 2, ANALOG_MODE, 2);

	SET_BITS(GPIOA->PUPDR, 0 * 2, NOPULL, 2);
	SET_BITS(GPIOA->PUPDR, 1 * 2, NOPULL, 2);

	//Change Injected channel sequence length to 2 conversions
	SET_BITS(ADC1->JSQR, 0, 1, 2);

	//Add channels to sequence
	SET_BITS(ADC1->JSQR, 8, 5, 4);
	SET_BITS(ADC1->JSQR, 14, 6, 4);

	//Disable Deep-power-down for ADC
	ADC1->CR &= ~(1 << 29);

	//Enable ADC Voltage regulator
	SET(ADC1->CR, ADC_ADVREGEN);

	//Configure for Single conversion mode
	RESET(ADC1->CFGR, ADC_CONT);

	//Enable ADC
	SET(ADC1->CR, ADC_ADEN);

	//Wait ADC is enabled
	while (!(ADC1->ISR & 1));

	//Enable interrupt for end of injected conversion
	SET(ADC1->IER, ADC_JEOSIE);
	SET(ISER1, 5);

	//Start regular conversion of ADC1
	SET(ADC1->CR, ADC_JADSTART);


	//Push button
	SET(RCC_AHB2ENR, GPIOEEN);

	SET_BITS(GPIOE->MODER, 15 * 2, INPUT_MODE, 2);
	SET_BITS(GPIOE->PUPDR, 15 * 2, PULLUP, 2);

	EXTI->EXTISR[15] = 4;
	SET(EXTI->IMR1, 15);
	SET(EXTI->FTSR1, 15);
	SET(ISER0, 26);
}


