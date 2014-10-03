@ read.S: read sycall wrapper
@
@ Authors: Group Member 1 <email address>
@          Group Member 2 <email address>
@ Date:    The current time & date

#include <bits/swi.h>
@#include <errno.h>
	@extern	errno
	.file	"read.S"
	.text
	.extern errno
	.global	read
read:
	swi	READ_SWI
	mov	r1, #0
	subs	r1, r1, r0
	@cmp r0, #0
	@movlt r0, #-1
	ble	.L1
	ldr	r0, =errno
	str	r1, [r0]
	mov	r0, #-1 

.L1:
	mov pc, lr
