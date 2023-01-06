/*
 * leds.h
 *
 *  Created on: 6 Jan 2023
 *      Author: batu
 */

#ifndef LEDS_H_
#define LEDS_H_

void init_TIM3();
void TIM3_IRQHandler(void);
void init_leds();
void set_direction(uint8_t d);
//0 -> forward 1->right 2 -> back 3-> left

#endif /* LEDS_H_ */
