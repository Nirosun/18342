/*
 * initialize irq interrupts
 */
#include <types.h>
#include <arm/reg.h> 
#include <arm/psr.h>
#include <arm/interrupt.h>
#include <exports.h>
#include "constant.h"

void irq_stack_setup(unsigned long stack);

void init_irq()
{
	void * irq_stack_block = (void *)malloc(irq_stack_size); // 512 bytes
	//unsigned long irq_Stack = (unsigned long)(irq_stack_block+512);

	reg_clear(INT_ICLR_ADDR, 1 << INT_OSTMR_0); // ignore FIQ
	reg_set(INT_ICMR_ADDR, 1 << INT_OSTMR_0);

	// irq sp: setup sp in irq mode
    irq_stack_setup((unsigned long)irq_stack_block+512); 
}
