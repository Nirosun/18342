/*
 * @file C_Irq_Handler
 *
 * when the timmer triger interrupt every 10ms,
 * jump to here: 
 * 		1. update system time
 *		2. fresh registers
 */
#include <exports.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <arm/interrupt.h>
//#include "constant.h"

extern unsigned long os_time;

void C_Irq_Handler()
{
	int icpr = reg_read(INT_ICIP_ADDR);
	uint32_t mask = 0x1 << INT_OSTMR_0;

#ifdef debug
	printf("enter c_irq_handler. \n");
#endif

	//uint32_t new_timmer = 0;

 	if(icpr & mask)
 	{
 	#ifdef debug
 		printf("right irq source (icpr:%d). inside c_irq_handler. \n",icpr);
 	#endif

 		os_time ++;	 // 10 ms

		/* restart */
 		reg_write(OSTMR_OSCR_ADDR, 0x00);
 		reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
 	}
 	else
 	{
 		printf("wrong irq source! where (%d) \n", icpr);
 	}
 	return;
 }
