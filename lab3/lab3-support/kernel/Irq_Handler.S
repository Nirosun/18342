/*
 * Irq handler: from sys. to user mode
 * 
 * function: save sp and jump to C_Irq_Handler
 * the only difference with S_Handler (temporary) is 
 * no arguments: SWI_Num, Stack pointer
 */
 .global Irq_Handler

Irq_Handler:
	sub	sp, sp, #4
	stmfd	sp!, {r0-r12, lr}	
	mrs	r2, spsr
	str	r2, [sp, #14*4]
	bl	C_Irq_Handler
	ldr	r2, [sp, #14*4]
	msr	spsr, r2
	ldmfd	sp!, {r0-r12, lr}	
	add	sp, sp, #4
	movs	pc, lr
