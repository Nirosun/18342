/*
 * @file init_irq.c
 *
 * initialize irq interrupts
 */
#include <types.h>
#include <arm/reg.h> 
#include <arm/psr.h>
#include <arm/interrupt.h>
#include <exports.h>
#include "../constant.h"

void _irq_stack_setup(unsigned long stack);
void _enable_irq();

void init_irq()
{	
	uint32_t icmr_mask, iclr_reg, iclr_mask;
	icmr_mask = (0x1 << INT_OSTMR_0);

	reg_write(INT_ICMR_ADDR, icmr_mask);
	iclr_reg = reg_read(INT_ICLR_ADDR);
	iclr_mask = ~(0x1 << INT_OSTMR_0);
	iclr_reg &= iclr_mask;

	reg_write(INT_ICLR_ADDR, iclr_reg);

	/*void * irq_stack_block = (void *)malloc(irq_stack_size); // 1024 bytes

	// irq sp: setup sp in irq mode
	_irq_stack_setup((unsigned long)irq_stack_block+1024); 
    
	_enable_irq();*/

    return;
}
