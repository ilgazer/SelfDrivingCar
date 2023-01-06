/*
 * timer.h
 *
 *  Created on: 27 Nov 2022
 *      Author: Ilgaz
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>


typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint16_t CNT;
	volatile uint16_t RESERVED_3;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
} TIM_t;

//CR1
#define CEN			0
#define UDIS		1
#define URS			2
#define OPM			3
#define ARPE		7
#define CKD			8
#define UIFREMAP	11

//CR2
#define CCPC		0
#define CCUS		2
#define CCDS		3
#define MMS			4
#define TI1S		7
#define OIS1		8
#define OIS1N		9
#define OIS2		10

//DIER
#define TDE		14
#define COMD	13
#define CC2DE	10
#define CC1DE	9
#define UDE		8
#define BIE		7
#define TIE		6
#define COMIE	5
#define CC2IE	2
#define CC1IE	1
#define UIE		0

//SR
#define CC2OF		10
#define CC1OF		9
#define BIF		7
#define TIF		6
#define COMIF		5
#define CC2IF		2
#define CC1IF		1
#define UIF		0

//CCMR1 input capture
// CC1S[1:0]
#define CC1S		0
// IC1PSC[1:0]
#define IC1PSC		2
// IC1F[3:0]
#define IC1F		4
// CC2S[1:0]
#define CC2S		8
// IC2PSC[1:0]
#define IC2PSC		10
// IC2F[3:0]
#define IC2F		12

//CCMR1 output compare
// CC1S[1:0]
#define CC1S		0
#define OC1FE		2
#define OC1PE		3
// OC1M[2:0]
#define OC1M		4
// CC2S[1:0]
#define CC2S		8
#define OC2FE		10
#define OC2PE		11
// OC2M[2:0]
#define OC2M		12
#define OC1M3		16
#define OC2M3		24

//OCxM modes
#define OCxM_PWM1 0b110
#define OCxM_PWM2 0b111

//CCxS modes
#define CCx_OUTPUT 		0
#define CCx_INPUT_TI1	1
#define CCx_INPUT_TI2	2
#define CCx_INPUT_TRC	3

//CCER
#define CC1E		0
#define CC1P		1
#define CC1NE		2
#define CC1NP		3
#define CC2E		4
#define CC2P		5
#define CC2NP		7

//Timers
#define TIM5            ((TIM_t *)	0x40000C00)
#define TIM4            ((TIM_t *)	0x40000800)
#define TIM3            ((TIM_t *)	0x40000400)
#define TIM2            ((TIM_t *)	0x40000000)
#define TIM15			((TIM_t *)	0x40014000)
#define TIM16			((TIM_t *)	0x40014400)


#endif /* TIMER_H_ */
