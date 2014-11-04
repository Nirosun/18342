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
 	if(reg_read(OSTMR_OSSR_ADDR) & OSTMR_OSSR_M0) && (reg_read(INT_ICPR_ADDR) >> INT_OSTMR_0))
 	{
 		os_time += 10;	

 	reg_write(OSTMR_OSSR_ADDR(0), reg_read(OSTMR_OSSR_ADDR(0)) + 32500);
 	
 	reg_set(OSTMR_OSSR_ADDR, OSTMR_OSSR_M0);
 	}
 	return;
 }