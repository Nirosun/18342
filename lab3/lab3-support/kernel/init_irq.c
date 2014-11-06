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
void Enable_Irq();

void init_irq()
{	
	uint32_t icmr_mask, iclr_reg, iclr_mask;
	icmr_mask = (0x1 << INT_OSTMR_0);

	reg_write(INT_ICMR_ADDR, icmr_mask);
	iclr_reg = reg_read(INT_ICLR_ADDR);
	iclr_mask = ~(0x1 << INT_OSTMR_0);
	iclr_reg &= iclr_mask;

	reg_write(INT_ICLR_ADDR, iclr_reg);

	void * irq_stack_block = (void *)malloc(irq_stack_size); // 512 bytes
	//unsigned long irq_Stack = (unsigned long)(irq_stack_block+512);

	//reg_clear(INT_ICLR_ADDR, 1 << INT_OSTMR_0); // ignore FIQ
	//reg_set(INT_ICMR_ADDR, 1 << INT_OSTMR_0);

	// irq sp: setup sp in irq mode
    irq_stack_setup((unsigned long)irq_stack_block+512); 
    
    Enable_Irq();

    return;
}
