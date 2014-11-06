/*
 * 
 */
#include <exports.h>
#include <arm/timer.h>
#include <arm/reg.h>
#include <arm/interrupt.h>

extern unsigned long os_time;

void C_Irq_Handler()
{
	int icpr = reg_read(INT_ICIP_ADDR);
	uint32_t mask = 0x1 << INT_OSTMR_0;

#ifdef debug
	printf("enter C_Irq_Handler. \n");
#endif

	uint32_t new_timmer = 0;

 	if(icpr & mask)
 	{
 	#ifdef debug
 		printf("right irq source (icpr:%d). inside C_Irq_Handler. \n",icpr);
 	#endif

 		os_time ++;	

 		new_timmer = reg_read(OSTMR_OSMR_ADDR(0));
		new_timmer += (OSTMR_FREQ*10)/1000;
		reg_write(OSTMR_OSMR_ADDR(0), new_timmer);

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
