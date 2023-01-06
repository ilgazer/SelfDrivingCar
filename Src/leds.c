

#include <stdint.h>
#include "leds.h"
#include "board/adc.h"
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
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
  volatile uint32_t OR1;
  volatile uint32_t CCMR3;
  volatile uint32_t CCR5;
  volatile uint32_t CCR6;
  volatile uint32_t OR2;
  volatile uint32_t OR3;
} TIM_TypeDef;

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
	uint32_t RESERVED;
	volatile uint32_t SECCFGR;
} GPIO_TypeDef;

#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))
#define RCC_APB2ENR *((volatile uint32_t *) (0x40021000 + 0x60))
#define RCC_APB1ENR *((volatile uint32_t *) (0x40021000 + 0x58))


#define GPIOB	((GPIO_TypeDef *)	0x42020400)
#define TIM3           ((TIM_TypeDef *)	0x40000400)
#define ISER1    *((volatile uint32_t *) (0xE000E104))


//PB0 front right
//PB1 front left
//PB2 back right
//PB3 back left

void init_TIM3()
{
RCC_APB1ENR |= 1 << 1; //TIM6x_CLK is enabled, running at 4MHz
 TIM3->EGR|=1;//enable UIF to generate an interrupt
 TIM3->PSC = 1999; //Set Prescaler
 TIM3->CR1 &= ~(1<<1); //OVF will generate an event
// TIM6 Interrupt Initialization
 TIM3->ARR = 500;
 TIM3->SR=0; //clear UIF if it is set
 TIM3->DIER |= 1;
 ISER1 |= 1 << 14;//enable global signaling for TIM6 interrupt
//
 TIM3->CR1 |= 1; //TIM6_CNT is enabled (clocked)
}


void init_leds(){
	__asm volatile( //enable all interrupts that are configured
	 "mov r0, #0 \n\t"
	 "msr primask, r0 \n\t"
	 );
	 RCC_AHB2ENR |= 1 << 1 ;
	 GPIOB->MODER &= ~(3 << 0);
	 GPIOB->MODER |= (1 << 0);

	 GPIOB->MODER &= ~(3 << 2);
	 GPIOB->MODER |= (1 << 2);

	 GPIOB->MODER &= ~(3 << 4);
	 GPIOB->MODER |= (1 << 4);

	 GPIOB->MODER &= ~(3 << 6);
	 GPIOB->MODER |= (1 << 6);

	 GPIOB->ODR = 0b1111;

	 init_TIM3();
}
static uint8_t led_direction;
void set_led_direction(uint8_t d){
	led_direction = d;
}
void TIM3_IRQHandler(void)
{
	switch (led_direction){
	case 0:
		GPIOB->ODR = 0b1100;
		break;
	case 2:
		GPIOB->ODR = 0b0011;
		break;
	case 1:
		GPIOB->ODR ^= 0b0101;
		break;
	case 3:
		GPIOB->ODR = (~GPIOB->ODR & 0b1010)| 0b0101;
		break;
	};
	TIM3->SR=0; //clear UIF
	ADC1->CR |= (1 << 2);
}


