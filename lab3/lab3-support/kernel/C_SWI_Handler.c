/*
 * C_SWI_Handler.c: Our swi handler in C.
 *
 * Author: Zhengyang Zuo <zzuo@andrew.cmu.edu>
 * Date:   Sun, 19 Oct 2014 08:42 PM
 */

#include <exports.h>
#include <bits/swi.h>

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
void exit();


void C_SWI_Handler (unsigned swi_num, unsigned *regs)
{

	switch (swi_num)
	{
	case EXIT_SWI:
		exit((int)regs[0]);
		break;
	case READ_SWI:	
		//printf("Before entering write.\n");	
		regs[0] = read(regs[0], (void *)regs[1], regs[2]);
		break;
	case WRITE_SWI:
		regs[0] = write(regs[0], (const void *)regs[1], regs[2]);
		break;
	default:
		printf("Error: swi not implemented: %x\n", swi_num);
		exit(0x0badc0de);
	}

}
