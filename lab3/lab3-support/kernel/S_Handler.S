/*
 * S_Handler.S: A re-entrant swi handler.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 09:12 PM
 */
	
	.global	S_Handler

S_Handler:
	sub	sp, sp, #4
	stmfd	sp!, {r0-r12, lr}	
	mrs	r2, spsr
	str	r2, [sp, #14*4]
	mov	r1, sp

	@ extract swi number
	ldr	r0, [lr, #-4]
	bic	r0, r0, #0xff000000
	bl	C_SWI_Handler

	ldr	r2, [sp, #14*4]
	msr	spsr, r2
	ldmfd	sp!, {r0-r12, lr}	
	add	sp, sp, #4
	movs	pc, lr
