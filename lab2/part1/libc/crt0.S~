@ crt0.S: Execution startup routine
@
@ Authors: Zhengyang Zuo <zzuo@andrew.cmu.edu>
@ Date:    10/06/2014, 2:24 PM

	.file	"crt0.S"
	.text

	.global	_start
_start:
	ldr r0, [sp]
	add r1, sp, #4
	bl main
	bl exit
