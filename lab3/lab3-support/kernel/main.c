#include <exports.h>

#include <bits/swi.h>
#include <bits/fileno.h>

#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/interrupt.h>
#include <arm/timer.h>

#include "constant.h"

void Install_Handler(unsigned *swi_vec_addr, unsigned *swi_handler_new, unsigned *swi_old_inst);
void Restore_Handler(unsigned *swi_vec_addr, unsigned *swi_old_inst);
unsigned S_Handler();
unsigned irq_handler();
int Load_User();
void init_irq();
void _disable_irq();
void init_os_time();

uint32_t global_data;

int kmain(int argc, char** argv, uint32_t table)
{
	app_startup(); /* bss is valid after this point */
	global_data = table;
	
	unsigned *swi_vec_addr = (unsigned *)0x08; 	
	unsigned *irq_vec_addr = (unsigned *)0x18; //IRQ vector entry	
	
	unsigned *swi_handler_new;
	unsigned *irq_handler_new;
	
	// first two instructions in old swi handler
	unsigned swi_old_inst[2];	

	// hold original irq handler
	unsigned irq_old_inst[2];

	int ret_val;

	swi_handler_new = (unsigned *)&S_Handler;
	irq_handler_new = (unsigned *)&irq_handler;
	printf("irq_handler_new:%p\n", irq_handler_new);

	// install new handler
	Install_Handler(swi_vec_addr, swi_handler_new, swi_old_inst);
	Install_Handler(irq_vec_addr, irq_handler_new, irq_old_inst);

	// initialization
	init_irq();
	init_os_time();

	ret_val = Load_User(argc, argv);

	_disable_irq();

	// restore old swi handler
	Restore_Handler(swi_vec_addr, swi_old_inst);
	Restore_Handler(irq_vec_addr, irq_old_inst);

	return ret_val;
}
