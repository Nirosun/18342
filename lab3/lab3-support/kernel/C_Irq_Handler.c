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
//#ifdef debug
	printf("enter C_Irq_Handler. \n");
//#endif
	int ossr = reg_read(OSTMR_OSSR_ADDR);
	int icpr = reg_read(INT_ICPR_ADDR);
 	if((ossr & OSTMR_OSSR_M0) && (icpr & 0x01 << INT_OSTMR_0))
 	{
 		printf("right irq source (mo). inside C_Irq_Handler. \n");
 		os_time ++;	
 		reg_write(OSTMR_OSCR_ADDR, 0x00);
 		reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
 	}
 	else
 	{
 		printf("wrong irq source! () \n");
 	}
 	return;
 }
