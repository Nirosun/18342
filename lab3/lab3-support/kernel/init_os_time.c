/*
 * initialize os timer
 */
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>

#define TIME_RESOLUTION	10 // 10 ms

volatile unsigned long os_time = 0;

 void init_os_time()
 {
 	unsigned long timer_trigger = OSTMR_FREQ*TIME_RESOLUTION/1000;
	 // set up registers for timer
	reg_write(OSTMR_OSCR_ADDR, 0x0);
	reg_write(OSTMR_OSMR_ADDR(0), timer_trigger);
	reg_write(OSTMR_OSSR_ADDR, 0x0); // clear status bit
	reg_write(OSTMR_OIER_ADDR, 0x01); // enable m0 only

	// ICCR???	 
	
 }
