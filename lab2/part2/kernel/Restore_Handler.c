/*
 * Restore_Handler.c: Restore the original swi handler.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 08:41 PM
 */

#include <exports.h>

void Restore_Handler(unsigned *swi_vec_addr, unsigned *swi_old_inst) 
{
	unsigned offset, *jmp_addr, *swi_handler_old;

	offset = *swi_vec_addr & 0x00000fff;
	if (*swi_vec_addr & 0x00800000)
	{
		jmp_addr = (unsigned *)((unsigned)swi_vec_addr + 8 + offset);
	}
	else
	{
		jmp_addr = (unsigned *)((unsigned)swi_vec_addr + 8 - offset);
	}
	swi_handler_old = (unsigned *)*jmp_addr;
	
	swi_handler_old[0] = swi_old_inst[0];
	swi_handler_old[1] = swi_old_inst[1];

}
