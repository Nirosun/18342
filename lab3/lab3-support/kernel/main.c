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
void init_irq();
void init_os_time();

#define stack_base	0xa3000000

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
	irq_handler_new = (unsigned *)&Irq_Handler;

	void reg (); // set up registers for timer
#ifdef debug
	printf("Before install handler. \n");
#endif
	// install new handler
	Install_Handler(swi_vec_addr, swi_handler_new, swi_old_inst);
	Install_Handler(irq_vec_addr, irq_handler_new, irq_old_inst);
#ifdef debug
	printf("After install handler. \n");
#endif

	// initialization
	init_irq();
	init_os_time();

	// init user args to stack, change oldsp_addr
	ret_val = Load_User(argc, argv);

	// restore old swi handler
	Restore_Handler(swi_vec_addr, swi_old_inst);
	Restore_Handler(irq_vec_addr, irq_old_inst);

	return ret_val;
}
