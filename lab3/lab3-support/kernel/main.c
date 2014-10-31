#include <exports.h>

#include <bits/swi.h>
#include <bits/fileno.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>

void Install_Handler(unsigned *swi_vec_addr, unsigned *swi_handler_new, unsigned *swi_old_inst);
void Restore_Handler(unsigned *swi_vec_addr, unsigned *swi_old_inst);
unsigned S_Handler();
int Load_User();

uint32_t global_data;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;
	
	unsigned *swi_vec_addr = (unsigned *)0x08;
	unsigned *swi_handler_new;
	unsigned swi_old_inst[2];	// first two instructions in old swi handler
	int ret_val;

	swi_handler_new = (unsigned *)&S_Handler;
	
	// install new swi handler
	Install_Handler(swi_vec_addr, swi_handler_new, swi_old_inst);

	printf("Before loading user program.\n");	

	ret_val = Load_User(argc, argv);

	// restore old swi handler
	Restore_Handler(swi_vec_addr, swi_old_inst);

	return ret_val;
}
