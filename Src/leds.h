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
void set_led_direction(uint8_t d);
//0 -> forward 1->right 2 -> back 3-> left

#define led_forward 0
#define led_right 1
#define led_back 2
#define led_left 3
#endif /* LEDS_H_ */
