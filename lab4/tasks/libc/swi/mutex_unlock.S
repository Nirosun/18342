/** @file time.S
 *
 * @brief time sycall wrapper
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-10-31
 */

#include <asm.h>
#include <bits/swi.h>

	.file "mutex_unlock.S"

FUNC(mutex_unlock)
	swi MUTEX_UNLOCK

	mov	r1, #0
	subs	r1, r1, r0
	ble	.L1
	ldr	r0, =errno
	str	r1, [r0]
	mov	r0, #-1 

.L1:
	mov pc, lr
