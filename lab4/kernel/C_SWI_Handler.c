/*
 * C_SWI_Handler.c: Our swi handler in C.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 *         Yang Wu <yangwu@andrew.cmu.edu>
 * Date:   Fri, 7 Nov 2014 08:53 PM
 */

#include <exports.h>
#include <bits/swi.h>

ssize_t read_syscall(int fd, void *buf, size_t count);
ssize_t write_syscall(int fd, const void *buf, size_t count);
void sleep_syscall(unsigned long millis);
unsigned long time_syscall(void);


void C_SWI_Handler (unsigned swi_num, unsigned *regs)
{

	switch (swi_num)
	{
	case READ_SWI:	
		regs[0] = read_syscall(regs[0], (void *)regs[1], regs[2]);
		break;
	case WRITE_SWI:
		regs[0] = write_syscall(regs[0], (const void *)regs[1], regs[2]);
		break;
	case TIME_SWI:
		regs[0] = (unsigned)time_syscall();
		break;
	case SLEEP_SWI:
		sleep_syscall((unsigned long)regs[0]);
		break;
	default:
		exit(0x0badc0de);
	}

}
