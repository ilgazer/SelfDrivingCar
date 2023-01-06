/*
 * adc.h
 *
 *  Created on: Dec 5, 2022
 *      Author: Ilgaz
 */

#ifndef ADC_H_
#define ADC_H_


typedef struct {
	volatile uint32_t ADC_ISR;
	volatile uint32_t ADC_IER;
	volatile uint32_t ADC_CR;
	volatile uint32_t ADC_CFGR;
	volatile uint32_t ADC_CFGR2;
	volatile uint32_t ADC_SMPR1;
	volatile uint32_t ADC_SMPR2;
	volatile uint32_t RESERVED;
	volatile uint32_t ADC_TR1;
	volatile uint32_t ADC_TR2;
	volatile uint32_t ADC_TR3;
	volatile uint32_t RESERVED2;
	volatile uint32_t ADC_SQR1;
	volatile uint32_t ADC_SQR2;
	volatile uint32_t ADC_SQR3;
	volatile uint32_t ADC_SQR4;
	volatile uint32_t ADC_DR;
} ADC_t;

typedef struct {
	volatile uint32_t ADC_CSR;
	volatile uint32_t RESERVED;
	volatile uint32_t ADC_CCR;
	volatile uint32_t ADC_CDR;
} ADC_shared_t;

//ADC_ISR

#define ADC_ADRDY		0
#define ADC_EOSMP		1
#define ADC_EOC			2
#define ADC_EOS			3
#define ADC_OVR			4
#define ADC_JEOC		5
#define ADC_JEOS		6
#define ADC_AWD1		7
#define ADC_AWD2		8
#define ADC_AWD3		9
#define ADC_JQOVF		10

//ADC_IER

#define ADC_ADRDYIE		0
#define ADC_EOSMPIE		1
#define ADC_EOCIE		2
#define ADC_EOSIE		3
#define ADC_OVRIE		4
#define ADC_JEOCIE		5
#define ADC_JEOSIE		6
#define ADC_AWD1IE		7
#define ADC_AWD2IE		8
#define ADC_AWD3IE		9
#define ADC_JQOVFIE		10


//ADC_CR

#define ADC_ADEN		0
#define ADC_ADDIS		1
#define ADC_ADSTART		2
#define ADC_JADSTART		3
#define ADC_ADSTP		4
#define ADC_JADSTP		5
#define ADC_ADVREGEN		28
#define ADC_DEEPPWD		29
#define ADC_ADCALDIF		30
#define ADC_ADCAL		31


//ADC_CFGR

#define ADC_DMAEN		0
#define ADC_DMACFG		1
#define ADC_DFSDMCFG	2
// RES[1:0]
#define ADC_RES			3
#define ADC_ALIGN		5
#define ADC_EXTSEL0		6
#define ADC_EXTSEL1		7
#define ADC_EXTSEL2		8
#define ADC_EXTSEL3		9
// EXTEN[1:0]
#define ADC_EXTEN		10
#define ADC_OVRMOD		12
#define ADC_CONT		13
#define ADC_AUTDLY		14
#define ADC_DISCEN		16
// DISCNUM[2:0]
#define ADC_DISCNUM		17
#define ADC_JDISC		20
#define ADC_JQM		21
#define ADC_AWD1SGL		22
#define ADC_AWD1EN		23
#define ADC_JAWD1EN		24
#define ADC_JAUTO		25
// AWD1CH[4:0]
#define ADC_AWD1CH		26
#define ADC_JQDIS		31


//ADC_CFGR2

#define ADC_ROVSE		0
#define ADC_JOVSE		1
// OVSR[2:0]
#define ADC_OVSR		2
// OVSS[3:0]
#define ADC_OVSS		5
#define ADC_TROVS		9
#define ADC_ROVSM		10


//ADC_SQR1

// L[3:0]
#define ADC_L		0
// SQ1[4:0]
#define ADC_SQ1		6
// SQ2[4:0]
#define ADC_SQ2		12
// SQ3[4:0]
#define ADC_SQ3		18
// SQ4[4:0]
#define ADC_SQ4		24


//ADC_CSR

#define ADC_ADRDY_MST		0
#define ADC_EOSMP_MST		1
#define ADC_EOC_MST			2
#define ADC_EOS_MST			3
#define ADC_OVR_MST			4
#define ADC_JEOC_MST		5
#define ADC_JEOS_MST		6
#define ADC_AWD1_MST		7
#define ADC_AWD2_MST		8
#define ADC_AWD3_MST		9
#define ADC_JQOVF_MST		10
#define ADC_ADRDY_SLV		16
#define ADC_EOSMP_SLV		17
#define ADC_EOC_SLV			18
#define ADC_EOS_SLV			19
#define ADC_OVR_SLV			20
#define ADC_JEOC_SLV		21
#define ADC_JEOS_SLV		22
#define ADC_AWD1_SLV		23
#define ADC_AWD2_SLV		24
#define ADC_AWD3_SLV		25
#define ADC_JQOVF_SLV		26

//ADC_CCR

// DUAL[4:0]
#define ADC_DUAL		0
// DELAY[3:0]
#define ADC_DELAY		8
#define ADC_ADCS_DMACFG	13
// MDMA[1:0]
#define ADC_MDMA		14
// CKMODE[1:0]
#define ADC_CKMODE		16
// PRESC[3:0]
#define ADC_PRESC		18
#define ADC_VREFEN		22
#define ADC_CH17SEL		23
#define ADC_CH18SEL		24


//ADCs

#define ADC1		((ADC_t *)			0x42028000)
#define ADC2		((ADC_t *)			0x42028100)
#define ADC_shared	((ADC_shared_t *)	0x42028300)


#endif /* ADC_H_ */
