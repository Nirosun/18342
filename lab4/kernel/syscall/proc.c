/** @file proc.c
 * 
 * @brief Implementation of `process' syscalls
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 14 Oct 2007 00:07:38 -0400
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-12
 */

#include <exports.h>
#include <bits/errno.h>
#include <config.h>
#include <kernel.h>
#include <syscall.h>
#include <sched.h>
#include <../sched/sched_i.h>
#include <lock.h>

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <device.h>
#include <util.h>

int task_create(task_t* tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    #ifdef DEBUG
    printf("inside task_create...\n");
    #endif

    disable_interrupts();

    if (num_tasks >= OS_AVAIL_TASKS || num_tasks <= 0)
    {
        enable_interrupts();
        return -EINVAL;
    }

    if(!valid_addr((void *)tasks, num_tasks, (uintptr_t)USR_START_ADDR, (uintptr_t)USR_END_ADDR))
    {
        enable_interrupts();
        return -EFAULT;
    }

    #ifdef DEBUG
    printf("ready for ub test...\n");
    #endif

    if (assign_schedule(&tasks, num_tasks) == 0) // ub_test fail
    { 
        enable_interrupts();
        return -ESCHED;
    }

    #ifdef DEBUG    
    printf("finish ub test...\n");
    #endif
    
    // Allocate user-stacks and init kernel contexts of thread
    allocate_tasks(&tasks, num_tasks);

    //sched_init(NULL);

    dispatch_nosave();

    return 0;
}

int event_wait(unsigned int dev  __attribute__((unused)))
{
    if(dev >= NUM_DEVICES)
    {
        return -EINVAL;
    }

    tcb_t* cur_tcb = get_cur_tcb();

    // if the current task holds a lock
    if(cur_tcb->holds_lock >= 1)
    {
        return -EHOLDSLOCK;
    }

    dev_wait(dev);

    return 0;
}

/* An invalid syscall causes the kernel to exit. */
void invalid_syscall(unsigned int call_num  __attribute__((unused)))
{
	printf("Kernel panic: invalid syscall -- 0x%08x\n", call_num);

	disable_interrupts();
	
    while(1);
}
