@ read.S: read sycall wrapper
@
@ Authors: Zhengyang Zuo <zzuo@andrew.cmu.edu>
@ Date:    10/06/2014, 2:24 PM

#include <bits/swi.h>
	.file	"read.S"
	.text
	.global	read
read:
	swi	READ_SWI
	mov	r1, #0
	subs	r1, r1, r0
	ble	.L1
	ldr	r0, =errno
	str	r1, [r0]
	mov	r0, #-1 

.L1:
	mov pc, lr
