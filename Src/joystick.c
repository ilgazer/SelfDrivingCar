#include "board/adc.h"
#include "board/rcc.h"
#include "board/gpio.h"
#include "board/iser.h"

void initialize_adc(){
	ADC_shared->CCR |= (0b1011 << 18);
	//Enable Clock for GPIO
		 RCC_AHB2ENR |= 0b111; // GPIOA-B-C is enabbled

		//Enable Clock for ADC

		 RCC_AHB2ENR |= 1 << 13; // ADC is enabbled

		//Select ADC clock as System clock
		 RCC_CCIPR1 |= (3 << 28);
	//	 ADC_CCR &= ~(3 << 16);
	//	 ADC_CCR |= (1 << 17);
		//Change Pin Mode to Analog
		 GPIOA->MODER |= 0b1111;


		//Change Pin Pull/Down to no pull-up no pull-down
		 GPIOA->PUPDR&=~(0b1111);

		//Change Regular channel sequence length to 1 conversion
	     ADC1->SQR1 &= ~(0b1111);
	     ADC1->SQR1 |= (0b1);

		//Add to channel to first sequence
	     ADC1->SQR1 &= ~(0b1111 << 6);
	     ADC1->SQR1 |= (5 << 6);

	     ADC1->SQR1 &= ~(0b1111 << 12);
	     ADC1->SQR1 |= (6 << 12);

		//Disable Deep-power-down for ADC
	     ADC1->CR &= ~(1 << 29);

		 //Enable ADC Voltage regulator
	     ADC1->CR |= (1 << 28);

		//Configure for Single conversion mode
	     ADC1->CFGR &= ~(1 << 13);

		//Enable ADC
	     ADC1->CR |= 1;

		//Wait ADC is enabled
	    while(!(ADC1->ISR &1));

		//Enable interrupt for end of regular conversion
	     ADC1->IER |= (1 << 2);
	     ISER1 |= 1 << 5;


		//Start regular conversion of ADCa
	     ADC1->CR |= (1 << 2);
}
