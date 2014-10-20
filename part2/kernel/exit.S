/*
 * exit.S: Handle exit syscall.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 09:11 PM
 */

#include <bits/addrno.h>

.global exit

exit:
        MOV   r1, #OLDSP_ADDR
        LDR   sp, [r1]
        LDMFD sp!, {r1-r12, lr}		@ restore original registers and stack
        MOV   pc, lr
