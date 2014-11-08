/*
 * @file irq_handler.S -from sys. to user mode
 * 
 * save sp and jump to C_Irq_Handler
 * the only difference with S_Handler (temporary) is 
 * no arguments: SWI_Num, Stack pointer
 */
 .global irq_handler
 .global _disable_irq
 .global _enable_irq

irq_handler:
	sub	sp, sp, #4
	stmfd	sp!, {r0-r12, lr}	    

	bl	_disable_irq				@ no more irq allowed
	bl	C_Irq_Handler

	msr cpsr, r12
	
	ldmfd	sp!, {r0-r12, lr}	
	add	sp, sp, #4
	
	subs	pc, lr, #4

_disable_irq:
	mrs r12, cpsr
	orr r12, r12, #0xc0
	msr cpsr, r12
	mov pc, lr

_enable_irq:
	mrs r12, cpsr
	bic r12, r12, #0x80
	msr cpsr, r12
	mov pc, lr
