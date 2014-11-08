/*
 * @file irq_stack_setup
 * 
 * 
 */
	.file "irq_stack_setup.S"
	.text

	.global _irq_stack_setup

_irq_stack_setup:
	mrs ip, cpsr
	bic ip, ip, #0x80	@ enable irq
	mov r2, ip

	bic	ip, ip, #0x1f
	orr ip, ip, #0x12	@ irq mode
	msr cpsr, ip

	mov sp, r0			@ install stack
	msr cpsr, r2
	mov pc, lr
