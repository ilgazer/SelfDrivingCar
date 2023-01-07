/*
 * leds.h
 *
 *  Created on: 6 Jan 2023
 *      Author: batu
 */

#ifndef LEDS_H_
#define LEDS_H_

typedef enum {LED_STOP, LED_FORWARD, LED_BACK, LED_RIGHT, LED_LEFT} led_direction;

void init_TIM3();
void TIM3_IRQHandler(void);
void init_leds();
void set_led_direction(led_direction d);


#endif /* LEDS_H_ */
