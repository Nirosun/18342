	.file "irq_stack_setup.S"
	.text

	.global irq_stack_setup

irq_stack_setup:
	mrs ip, cpsr
	orr ip, ip, #0x12
	msr cpsr, ip 		@ change to IRQ mode
	ldr sp, [r0]		@ allocate irq_sp to irq_stack
	mrs ip, cpsr
	orr ip, ip, #0x13
	orr ip, ip, #0x80	@ enable IRQ
	msr cpsr, ip 		@ change back to svc mode
	mov pc, lr
