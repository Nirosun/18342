@ hello.S: Hello world! in assembly
@
@ Authors: Zhengyang Zuo <zzuo@andrew.cmu.edu>
@ Date:    10/06/2014, 2:22 PM

#include <bits/swi.h>
#include <bits/fileno.h>

	.file	"hello.S"
	.text

	.global	_start
_start:
	mov r0, #STDOUT_FILENO
	adr r1, hello_str
	mov r2, #hello_size
	swi WRITE_SWI
	mov r0, #0
	swi EXIT_SWI

hello_str:
	.ascii	"Hello world!\n"
	.set	hello_size, .-hello_str
