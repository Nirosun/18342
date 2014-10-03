@ write.S: write sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>

	.file	"write.S"
	.text
	.extern errno
	.global	write
write:
	swi	WRITE_SWI
	mov	r1, #0
	subs	r1, r1, r0
	ble	.L1
	@cmp r0, #0
	ldr	r0, =errno
	str	r1, [r0]
	mov	r0, #-1
.L1:
	mov	pc, lr
