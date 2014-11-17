/** @file sched.c
 * 
 * @brief Top level implementation of the scheduler.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-20
 */

#include <types.h>
#include <assert.h>

#include <kernel.h>
#include <config.h>
#include "sched_i.h"

#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <arm/physmem.h>
#include <util.h>

tcb_t system_tcb[OS_MAX_TASKS]; /*allocate memory for system TCBs */

/**
 * @brief set up the tcb for the ith task
 */
void setup_task_context(task_t *task, tcb_t *tcb, uint8_t prio) {
    sched_context_t *context = &(tcb->context);

    context->r4  = (uint32_t)task->lambda;
    context->r5  = (uint32_t)task->data;
    context->r6  = (uint32_t)task->stack_pos;
    context->r7  = 0;
    context->r8  = global_data;
    context->r9  = 0;
    context->r10 = 0;
    context->r11 = 0;
    context->sp  = (void *)tcb->kstack_high;
    context->lr  = launch_task;
    
    tcb->native_prio = prio;
    tcb->cur_prio = prio;
    tcb->holds_lock = 0;
    tcb->sleep_queue = NULL;
}

/**
 * @brief This is the idle task that the system runs when no other task is runnable
 */

static void __attribute__((unused)) idle(void)
{
    enable_interrupts();
    while(1);
}

/**
 * @brief set up IDLE task tcb
 */

void sched_init(task_t* main_task  __attribute__((unused)))
{
    tcb_t *idle_tcb = &(system_tcb[IDLE_PRIO]);
    sched_context_t *context = &(idle_tcb->context);

    context->r4  = (uint32_t)idle;
    context->r5  = (uint32_t)NULL;
    context->r6  = (uint32_t)NULL;
    context->r7  = 0;
    context->r8  = global_data;
    context->r9  = 0;
    context->r10 = 0;
    context->r11 = 0;
    context->sp  = idle_tcb->kstack_high;
    context->lr  = launch_task;

    idle_tcb->native_prio = IDLE_PRIO;
    idle_tcb->cur_prio = IDLE_PRIO;
    idle_tcb->holds_lock = 0;
    idle_tcb->sleep_queue = NULL;

    // Add the IDLE task to run queue
    runqueue_add(idle_tcb, IDLE_PRIO);
}

/**
 * @brief Allocate user-stacks and initializes the kernel contexts of the
 * given threads.
 *
 * This function assumes that:
 * - num_tasks < number of tasks allowed on the system.
 * - the tasks have already been deemed schedulable and have been appropriately
 *   scheduled.  In particular, this means that the task list is sorted in order
 *   of priority -- higher priority tasks come first.
 *
 * @param tasks  A list of scheduled task descriptors.
 * @param size   The number of tasks is the list.
 */
void allocate_tasks(task_t** tasks  __attribute__((unused)), size_t num_tasks  __attribute__((unused)))
{
    size_t i;

    for (i = 1; i <= num_tasks; i++) {
        // Create tcb for current task
        setup_task_context(&(*tasks)[i - 1], &system_tcb[i], i);

        // Add current task to run queue
        runqueue_add(&system_tcb[i], i);
    }
}
