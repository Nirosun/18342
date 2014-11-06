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
	bl	test
	sub	sp, sp, #4
	stmfd	sp!, {r0-r12, lr}	
	@mrs	r2, spsr       
	@str	r2, [sp, #14*4]
	bl	Disable_Irq				@ no more irq allowed
	bl	C_Irq_Handler
	ldr	r2, [sp, #14*4]
	msr	spsr, r2
	bl 	Enable_Irq
	ldmfd	sp!, {r0-r12, lr}	
	add	sp, sp, #4
	subs	pc, lr, #4

Disable_Irq:
	stmfd 	sp!, {r4, lr}
	mrs 	r4, cpsr
	orr 	r4,r4, #0xC0
	msr 	cpsr, r4
	ldmfd 	sp!, {r4, pc}

Enable_Irq:
	stmfd	sp!, {r4, lr}
	mrs 	r4, cpsr
	bic 	r4, r4, #0x80
	msr 	cpsr, r4
	ldmfd	sp!, {r4, pc}
