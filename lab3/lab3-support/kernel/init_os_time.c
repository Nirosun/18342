/*
 * initialize os timer
 */
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <exports.h>
#include <arm/interrupt.h>

#define TIME_RESOLUTION	10 // 10 ms

volatile unsigned long os_time = 1;

 void init_os_time()
 {
 	//unsigned long timer_trigger = OSTMR_FREQ*TIME_RESOLUTION/1000; //32500
 	printf("timer_trigger:%d\n", 32500);
	 // set up registers for timer
	//reg_write(OSTMR_OSCR_ADDR, 0x0);
	//reg_write(OSTMR_OSMR_ADDR(0), timer_trigger);
	//reg_write(OSTMR_OIER_ADDR, OSTMR_OIER_E0); // enable m0 only
	//reg_clear(INT_ICLR_ADDR, 1 << INT_OSTMR_0);
	
	// match oscr against osmr0
	reg_set(INT_ICMR_ADDR, 1 << INT_OSTMR_0);
	
	// set the matched value in osmr0
	reg_write(OSTMR_OSMR_ADDR(0), 32500);
	
	// let oscr count from 0
	reg_write(OSTMR_OSCR_ADDR, 0);
	
	// let oscr count from beginning
	reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
 }
