/*
 * lpuart.c
 *
 *  Created on: 19 Dec 2022
 *      Author: Ilgaz
 */

#ifndef LPUART_H_
#define LPUART_H_

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t BRR;
	volatile uint32_t RESERVED[2];
	volatile uint32_t RQR;
	volatile uint32_t ISR;
	volatile uint32_t ICR;
	volatile uint32_t RDR;
	volatile uint32_t TDR;
	volatile uint32_t PRESC;
} LPUART_t;

#define LPUART ((volatile LPUART_t *) (0x40008000))

//CR1
#define LPUART_UE		0
#define LPUART_UESM		1
#define LPUART_RE		2
#define LPUART_TE		3
#define LPUART_IDLEIE		4
#define LPUART_RXFNEIE		5
#define LPUART_TCIE		6
#define LPUART_TXFNFIE		7
#define LPUART_PEIE		8
#define LPUART_PS		9
#define LPUART_PCE		10
#define LPUART_WAKE		11
#define LPUART_M0		12
#define LPUART_MME		13
#define LPUART_CMIE		14
// DEDT[4:0]
#define LPUART_DEDT		16
// DEAT[4:0]
#define LPUART_DEAT		21
#define LPUART_M1		28
#define LPUART_FIFOEN		29
#define LPUART_TXFEIE		30
#define LPUART_RXFFIE		31

//CR2
#define LPUART_ADDM7		4
// STOP [1:0]
#define LPUART_STOP 		12
#define LPUART_SWAP		15
#define LPUART_RXINV		16
#define LPUART_TXINV		17
#define LPUART_DATAINV		18
#define LPUART_MSBFIRST		19
// ADD[7:0]
#define LPUART_ADD		24

//CR3
#define LPUART_EIE		0
#define LPUART_HDSEL		3
#define LPUART_DMAR		6
#define LPUART_DMAT		7
#define LPUART_RTSE		8
#define LPUART_CTSE		9
#define LPUART_CTSIE		10
#define LPUART_OVRDIS		12
#define LPUART_DDRE		13
#define LPUART_DEM		14
#define LPUART_DEP		15
// WUS [1:0]
#define LPUART_WUS 		20
#define LPUART_WUFIE		22
#define LPUART_TXFTIE		23
// RXFTCFG[2:0]
#define LPUART_RXFTCFG		25
#define LPUART_RXFTIE		28
// TXFTCFG[2:0]
#define LPUART_TXFTCFG		29

//RQR
#define LPUART_SBKRQ		1
#define LPUART_MMRQ		2
#define LPUART_RXFRQ		3
#define LPUART_TXFRQ		4

//ISR
#define LPUART_PE		0
#define LPUART_FE		1
#define LPUART_NE		2
#define LPUART_ORE		3
#define LPUART_IDLE		4
#define LPUART_RXFNE		5
#define LPUART_TC		6
#define LPUART_TXFNF		7
#define LPUART_CTSIF		9
#define LPUART_CTS		10
#define LPUART_BUSY		16
#define LPUART_CMF		17
#define LPUART_SBKF		18
#define LPUART_RWU		19
#define LPUART_WUF		20
#define LPUART_TEACK		21
#define LPUART_REACK		22
#define LPUART_TXFF		23
#define LPUART_RXFF		24
#define LPUART_RXFT		26
#define LPUART_TXFT		27

//ICR
#define LPUART_PECF		0
#define LPUART_FECF		1
#define LPUART_NECF		2
#define LPUART_ORECF		3
#define LPUART_IDLECF		4
#define LPUART_TCCF		6
#define LPUART_CTSCF		9
#define LPUART_CMCF		17
#define LPUART_WUCF		20

#endif /* LPUART_H_ */
