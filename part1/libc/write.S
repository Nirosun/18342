@ write.S: write sycall wrapper
@
@ Authors: Zhengyang Zuo
@ Date:    10/06/2014, 2:24 PM

#include <bits/swi.h>

	.file	"write.S"
	.text
	.global	write
write:
	swi	WRITE_SWI
	mov	r1, #0
	subs	r1, r1, r0
	ble	.L1
	ldr	r0, =errno
	str	r1, [r0]
	mov	r0, #-1
.L1:
	mov	pc, lr
