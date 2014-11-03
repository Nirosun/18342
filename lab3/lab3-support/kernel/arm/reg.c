#include <types.h>

#define IMPLEMENTATION
#include <arm/reg.h>
#include <arm/timer.h>
#include <arm/interrupt.h>

void reg ()
{
	// set up registers for timer
	 reg_set(OSTMR_OSCR_ADDR, 0x0);
	 reg_set(OSTMR_OSMR_ADDR(0), 0x9eb10); //650,000 cycles: 200ms
	 reg_set(OSTMR_OSSR_ADDR, 0x0); // clear status bit
	 reg_set(OSTMR_OIER_ADDR, 0x01); // enable m0 only

	 // set up interrupt controller
	 reg_set(INT_ICLR_ADDR, 0x0); // ignore FIQ
	 reg_set(INT_ICMR_ADDR, 0x4000000); // only interrupt from OSMR0=OSCR unmarked
	 reg_set(INT_ICPR_ADDR, 0x0); // initial pending reg
	// ICCR???	 
}
