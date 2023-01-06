/*
 * iser.c
 *
 *  Created on: Jan 7, 2023
 *      Author: Ilgaz
 */


void enable_interrupts(){
	__asm volatile(  //enable all interrupts that are configured
			"mov r0, #0 \n\t"
			"msr primask, r0 \n\t"
	);
}

void wfi(){
	__asm volatile("wfi");
}
