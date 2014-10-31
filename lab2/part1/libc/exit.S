@ exit.S: exit sycall wrapper
@
@ Authors: Zhengyang Zuo <zzuo@andrew.cmu.edu>
@ Date:    10/06/2014, 2:23 PM

#include <bits/swi.h>

	.file	"exit.S"
	.text

	.global	exit
exit:
	SWI	EXIT_SWI
