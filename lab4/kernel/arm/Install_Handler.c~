/*
 * Install_Handler.c: Install our swi handler.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 08:38 PM
 */

#include <exports.h>

void exit();

void Install_Handler(unsigned *swi_vec_addr, unsigned *swi_handler_new, unsigned *swi_old_inst) 
{
	unsigned offset, *jmp_addr, *swi_handler_old;

#ifdef debug
	int i=0;
	printf("current swi_vec_addr:%p\n", swi_vec_addr);
	if(swi_vec_addr==(unsigned *)0x18)
	{
		printf("matched!\n");
		i=1;
	}
#endif

	if (((*swi_vec_addr & 0xfffff000) != 0xe59ff000) && 
		((*swi_vec_addr & 0xfffff000) != 0xe51ff000))
	{
		printf("The instruction (%x) at swi vector address is not a load instruction.\n", *swi_vec_addr);
		exit(0x0badc0de);
		return;
	}

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

	swi_old_inst[0] = *swi_handler_old;
	swi_old_inst[1] = *(swi_handler_old + 1);
	swi_handler_old[0] = 0xe51ff004;	// This is "LDR pc, [pc, #-4]"
	swi_handler_old[1] = (unsigned)swi_handler_new;
	
#ifdef debug
	if(i==1)
		printf("now, irq handler is %x and %x\n", swi_handler_old[0], swi_handler_old[1]);
#endif
}
