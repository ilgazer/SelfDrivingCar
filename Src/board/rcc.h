/*
 * rcc.h
 *
 *  Created on: Dec 5, 2022
 *      Author: Ilgaz
 */

#ifndef RCC_H_
#define RCC_H_

#include <stdint.h>

//RCC_AHB2ENR

#define GPIOAEN		0
#define GPIOBEN		1
#define GPIOCEN		2
#define GPIODEN		3
#define GPIOEEN		4
#define GPIOFEN		5
#define GPIOGEN		6
#define GPIOHEN		7
#define ADCEN		13
#define AESEN		16
#define HASHEN		17
#define RNGEN		18
#define PKAEN		19
#define OTFDEC1EN		21
#define SDMMC1EN		22


//APB1ENR1

#define TIM2EN		0
#define TIM3EN		1
#define TIM4EN		2
#define TIM5EN		3
#define TIM6EN		4
#define TIM7EN		5
#define RTCAPBEN		10
#define WWDGEN		11
#define SPI2EN		14
#define SPI3EN		15
#define USART2EN		17
#define USART3EN		18
#define UART4EN		19
#define UART5EN		20
#define I2C1EN		21
#define I2C2EN		22
#define I2C3EN		23
#define CRSEN		24
#define PWREN		28
#define DAC1EN		29
#define OPAMPEN		30
#define LPTIM1EN		31


//APB1ENR2

#define LPUART1EN		0
#define I2C4EN		1
#define LPTIM2EN		5
#define LPTIM3EN		6
#define FDCAN1EN		9
#define USBFSEN		21
#define UCPD1EN		23


//APB2ENR

#define SYSCFGEN		0
#define TIM1EN		11
#define SPI1EN		12
#define TIM8EN		13
#define USART1EN		14
#define TIM15EN		16
#define TIM16EN		17
#define TIM17EN		18
#define SAI1EN		21
#define SAI2EN		22
#define DFSDM1EN		24


//RCC_CCIPR1

// USART1SEL[1:0]
#define USART1SEL		0
// USART2SEL[1:0]
#define USART2SEL		2
// USART3SEL[1:0]
#define USART3SEL		4
// UART4SEL[1:0]
#define UART4SEL		6
// UART5SEL[1:0]
#define UART5SEL		8
// LPUART1SEL[1:0]
#define LPUART1SEL		10
// I2C1SEL[1:0]
#define I2C1SEL			12
// I2C2SEL[1:0]
#define I2C2SEL			14
// I2C3SEL[1:0]
#define I2C3SEL			16
// LPTIM1SEL[1:0]
#define LPTIM1SEL		18
// LPTIM2SEL[1:0]
#define LPTIM2SEL		20
// LPTIM3SEL[1:0]
#define LPTIM3SEL		22
// FDCANSEL[1:0]
#define FDCANSEL		24
// CLK48MSEL[1:0]
#define CLK48MSEL		26
// ADCSEL[1:0]
#define ADCSEL			28


#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))
#define RCC_APB1ENR1 *((volatile uint32_t *) (0x40021000 + 0x58))
#define RCC_APB1ENR2 *((volatile uint32_t *) (0x40021000 + 0x5C))
#define RCC_APB2ENR *((volatile uint32_t *) (0x40021000 + 0x60))
#define RCC_CCIPR1 *((volatile uint32_t *) (0x40021000 + 0x88))
#define RCC_CFGR *((volatile uint32_t *) (0x40021000 + 0x08))


#endif /* RCC_H_ */
