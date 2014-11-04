/*
 * initialize irq interrupts
 */
#include <types.h>
#include <arm/reg.h> 
#include <arm/psr.h>
#include <arm/interrupt.h>

void init_irq()
{
	void * irq_stack = (void *)(0xa3f00000 + 0x200); // 512 bytes

	reg_set(INT_ICLR_ADDR, 0x0); // ignore FIQ
	reg_set(INT_ICMR_ADDR, 0x4000000); // only interrupt from OSMR0=OSCR unmarked
	reg_set(INT_ICPR_ADDR, 0x0); // clear pending reg

	// irq sp: setup sp in irq mode
    irq_stack_setup(irq_stack); 
}
