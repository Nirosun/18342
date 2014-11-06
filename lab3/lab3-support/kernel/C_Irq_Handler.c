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
#ifdef debug
	printf("enter C_Irq_Handler. \n");
#endif
	//int ossr = reg_read(OSTMR_OSSR_ADDR);
	int icpr = reg_read(INT_ICIP_ADDR);
	uint32_t mask = 0x1 << INT_OSTMR_0;

	uint32_t ossr, clocks_till_interrupt = 0;

 	//if((ossr & OSTMR_OSSR_M0) && (icpr & 0x01 << INT_OSTMR_0))
 	if(icpr & mask)
 	{
 	#ifdef debug
 		printf("right irq source (icpr:%d). inside C_Irq_Handler. \n",icpr);
 	#endif

 		os_time ++;	

 		clocks_till_interrupt = reg_read(OSTMR_OSMR_ADDR(0));
		clocks_till_interrupt += (OSTMR_FREQ*10)/1000;
		reg_write(OSTMR_OSMR_ADDR(0), clocks_till_interrupt);

		ossr = reg_read(OSTMR_OSSR_ADDR);
		ossr |= OSTMR_OSSR_M0;
		reg_write(OSTMR_OSSR_ADDR, ossr);

		ossr = reg_read(OSTMR_OSSR_ADDR);
 		reg_write(OSTMR_OSCR_ADDR, 0x00);
 		reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
 	}
 	else
 	{
 		printf("wrong irq source! where (%d) \n", icpr);
 	}
 	return;
 }
