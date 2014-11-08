/*
 * C_SWI_Handler.c: Our swi handler in C.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 *         Yang Wu <yangwu@andrew.cmu.edu>
 * Date:   Fri, 7 Nov 2014 08:53 PM
 */

#include <exports.h>
#include <bits/swi.h>

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
void sleep(int time);
void exit();
size_t time();


void C_SWI_Handler (unsigned swi_num, unsigned *regs)
{

	switch (swi_num)
	{
	case EXIT_SWI:
		exit((int)regs[0]);
		break;
	case READ_SWI:	
		regs[0] = read(regs[0], (void *)regs[1], regs[2]);
		break;
	case WRITE_SWI:
		regs[0] = write(regs[0], (const void *)regs[1], regs[2]);
		break;
	case TIME_SWI:
		regs[0] = time();
		break;
	case SLEEP_SWI:
		sleep((unsigned int)regs[0]);
		break;
	default:
		exit(0x0badc0de);
	}

}
