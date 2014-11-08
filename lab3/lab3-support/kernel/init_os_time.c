/*
 * @file init_os_time.c
 *
 * initialize os timer registers
 */
#include <types.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <exports.h>
#include <arm/interrupt.h>
#include "constant.h"

volatile unsigned long os_time = 0;

 void init_os_time()
 {
	 /* set up registers for timer */
	reg_write(OSTMR_OSCR_ADDR, 0x0);
	reg_write(OSTMR_OSMR_ADDR(0), osmr_value);
	
	/* enable oscr */
	reg_set(OSTMR_OIER_ADDR, OSTMR_OIER_E0);
 }
