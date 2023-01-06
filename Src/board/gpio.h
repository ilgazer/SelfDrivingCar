/*
 * gpio.h
 *
 *  Created on: Dec 5, 2022
 *      Author: Ilgaz
 */

#ifndef GPIO_H_
#define GPIO_H_

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
	volatile uint32_t BRR;
	uint32_t RESERVED;
	volatile uint32_t SECCFGR;
} GPIO_TypeDef;

#define GPIOA			((GPIO_TypeDef *)	0x42020000)
#define GPIOB			((GPIO_TypeDef *)	0x42020400)
#define GPIOC			((GPIO_TypeDef *)	0x42020800)
#define GPIOD			((GPIO_TypeDef *)	0x42020C00)
#define GPIOE			((GPIO_TypeDef *)	0x42021000)
#define GPIOF			((GPIO_TypeDef *)	0x42021400)
#define GPIOG			((GPIO_TypeDef *)	0x42021800)
#define GPIOH			((GPIO_TypeDef *)	0x42021C00)

#define INPUT_MODE 0
#define OUTPUT_MODE 1
#define ALTERNATE_MODE 2
#define ANALOG_MODE 3

#define NOPULL 0
#define PULLUP 1
#define PULLDOWN 2


#endif /* GPIO_H_ */
