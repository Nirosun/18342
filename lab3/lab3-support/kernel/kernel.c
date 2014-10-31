/*
 * kernel.c: Kernel main (entry) function
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 08:26 PM
 */

#include <exports.h>
#include <bits/swi.h>
#include <bits/fileno.h>

void Install_Handler(unsigned *swi_vec_addr, unsigned *swi_handler_new, unsigned *swi_old_inst);
void Restore_Handler(unsigned *swi_vec_addr, unsigned *swi_old_inst);
unsigned S_Handler();
int Load_User();

int main(int argc, char *argv[]) {

	unsigned *swi_vec_addr = (unsigned *)0x08;
	unsigned *swi_handler_new;
	unsigned swi_old_inst[2];	// first two instructions in old swi handler
	int ret_val;

	swi_handler_new = (unsigned *)&S_Handler;
	
	// install new swi handler
	Install_Handler(swi_vec_addr, swi_handler_new, swi_old_inst);	

	ret_val = Load_User(argc, argv);

	// restore old swi handler
	Restore_Handler(swi_vec_addr, swi_old_inst);

	return ret_val;
}
