/*
 * Irq handler: from sys. to user mode
 * 
 * function: save sp and jump to C_Irq_Handler
 * the only difference with S_Handler (temporary) is 
 * no arguments: SWI_Num, Stack pointer
 */
 .global Irq_Handler
 .global Disable_Irq
 .global Enable_Irq

Irq_Handler:
	@ bl	test
	@sub	sp, sp, #4
	stmfd	sp!, {r0-r12, lr}	    

	@ bl	Disable_Irq				@ no more irq allowed
	bl	C_Irq_Handler

	@msr	spsr, r2
	msr cpsr, r12
	
	ldmfd	sp!, {r0-r12, lr}	
	@add	sp, sp, #4
	
	subs	pc, lr, #4

Disable_Irq:
	mrs r12, cpsr
	orr r12, r12, #0xc0
	msr cpsr, r12
	mov pc, lr

Enable_Irq:
	mrs r12, cpsr
	bic r12, r12, #0x80
	msr cpsr, r12
	mov pc, lr
