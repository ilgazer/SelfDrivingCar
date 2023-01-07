/*
 * exti.h
 *
 *  Created on: Jan 7, 2023
 *      Author: Ilgaz
 */

#ifndef BOARD_EXTI_H_
#define BOARD_EXTI_H_

typedef struct {
	volatile uint32_t RTSR1;
	volatile uint32_t FTSR1;
	volatile uint32_t SWIER1;
	volatile uint32_t RPR1;
	volatile uint32_t FPR1;
	volatile uint32_t SECCFGR1;
	volatile uint32_t PRIVCFGR1;
	volatile uint32_t RESERVED;
	volatile uint32_t RTSR2;
	volatile uint32_t FTSR2;
	volatile uint32_t SWIER2;
	volatile uint32_t RPR2;
	volatile uint32_t FPR2;
	volatile uint32_t SECCFGR2;
	volatile uint32_t PRIVCFGR2;
	volatile uint32_t RESERVED_2[9];
	volatile uint8_t EXTISR[16];
	volatile uint32_t LOCKR;
	volatile uint32_t RESERVED_3[3];
	volatile uint32_t IMR1;
	volatile uint32_t EMR1;
	volatile uint32_t RESERVED_4[2];
	volatile uint32_t IMR2;
	volatile uint32_t EMR2;
} EXTI_t;

#define EXTI ((EXTI_t *) 0x4002F400)

#endif /* BOARD_EXTI_H_ */
