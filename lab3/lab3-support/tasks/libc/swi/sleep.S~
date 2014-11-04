/** @file sleep.S
 *
 * @brief sleep sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <asm.h>

	.file "sleep.S"
	.global sleep

FUNC(sleep)
sleep:
	stmfd sp!,{r1-r12, lr}
	swi SLEEP_SWI
	ldmfd sp!,{r1-r12, lr}
	mov pc, lr
