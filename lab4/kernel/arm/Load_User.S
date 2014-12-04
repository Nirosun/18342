/*
 * @file Load_User.S: 
 *
 * Do preparaing work and load user program.
 *
 */

#include <bits/swi.h>
#include <config.h>

.global Load_User

Load_User:
        stmfd	sp!, {r1-r12, lr}
        ldr	r2, =OLDSP_ADDR
        str	sp, [r2]		@ store original registers and stack
        mrs	r3, cpsr
        bic	r3, r3, #0x000000ff
        orr	r3, r3, #0x000000d0
        msr	cpsr, r3		@ change cpsr to user mode and mask I,F
        ldr	sp, =USR_STACK	        @ setup user mode stack
        mov	r2, #0
        str	r2, [sp, #-4]!		@ push <NULL> on top of stack
        mov	r3, r0
@	mov	r3, r3, LSL #2

        @ r8!r8!r8!
        ldr r12, =global_data
        ldr r8, [r12]
@.L1:       
@        subs	r3, r3, #4
@        blt	.L2
@        ldr	r2, [r1, r3]
@        str	r2, [sp, #-4]!		@ push argv on user stack
@        b	.L1
@.L2:
@	str	r0, [sp, #-4]!		@ push argc on user stack
        ldr	pc, =LOAD_ADDR
