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
int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)));
int mutex_create(void);
int mutex_lock(int mutex  __attribute__((unused)));
int mutex_unlock(int mutex  __attribute__((unused)));
int event_wait(unsigned int dev  __attribute__((unused)));

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
	case CREATE_SWI:
		regs[0] = task_create((task_t *)regs[0], (size_t)regs[1]);
		break;
	case MUTEX_CREATE:
		regs[0] = mutex_create();
		break;
	case MUTEX_LOCK:
		regs[0] = mutex_lock(regs[0]);
		break;
	case MUTEX_UNLOCK:
		regs[0] = mutex_unlock(regs[0]);
		break;
	case EVENT_WAIT:
		regs[0] = event_wait((unsigned int)regs[0]);
		break;
	default:
		exit(0x0badc0de);
	}

}
