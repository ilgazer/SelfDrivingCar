/*
 * pins.h
 *
 *  Created on: 12 Jan 2023
 *      Author: Ilgaz
 */

#ifndef PINS_H_
#define PINS_H_

//Motor driver pin mappings

#define DRV_PORT GPIOC

#define DRV_IN1		9		//PC9
#define DRV_IN2		10		//PC10
#define DRV_IN3		11		//PC11
#define DRV_IN4		12		//PC12

#define DRV_EN_PORT GPIOA

#define DRV_ENA 	2		//PA2
#define DRV_ENB 	3		//PA3

//ADC reading pins
#define JOY_PORT	GPIOA

#define JOY_VRx		0		//PA0
#define JOY_VRy		1		//PA1

#define LDR_PORT	GPIOC

#define LDR_R		0		//PC0
#define LDR_L		1		//PC1

//EXTI pins

#define JOY_BTN		6		//PA6
#define BLUE_BTN	13		//PC13

//Ultrasonic pins
//ECHO						//PC6
//TRIG						//PC8

//LED pins
#define LED_PORT GPIOE

#define LED_FR		12		//PE12
#define LED_FL		13		//PE13
#define LED_BR		14		//PE14
#define LED_BL		15		//PE15


#endif /* PINS_H_ */
