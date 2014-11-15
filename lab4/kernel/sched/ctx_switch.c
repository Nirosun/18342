/** @file ctx_switch.c
 * 
 * @brief C wrappers around assembly context switch routines.
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-11-21
 */
 

#include <types.h>
#include <assert.h>

#include <config.h>
#include <kernel.h>
#include "sched_i.h"

#ifdef DEBUG_MUTEX
#include <exports.h>
#endif

static __attribute__((unused)) tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
	cur_tcb = idel;	
}


/**
 * @brief Context switch to the highest priority task while saving off the 
 * current task state.
 *
 * This function needs to be externally synchronized.
 * We could be switching from the idle task.  The priority searcher has been tuned
 * to return IDLE_PRIO for a completely empty run_queue case.
 */
void dispatch_save(void)
{
	uint8_t highest_prio = highest_prio();

	// place cur tcb in queue, wait for next time slice
	runqueue_add(cur_tcb, cur_tcb->cur_prio);
	tcb_t* temp_tcb = cur_tcb;
	// get task with highest prio in ready list
	tcb_t* next_tcb =runqueue_remove(highest_prio);
	cur_tcb = next_tcb;

	// ctx switch to new task
	ctx_switch_full(&(next_tcb->context), &(temp_tcb->context));
}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * don't save the current task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
	uint8_t highest_prio = highest_prio();

	runqueue_add(cur_tcb, cur_tcb->cur_prio);
	tcb_t* temp_tcb = cur_tcb;
	// get task with highest prio in ready list
	tcb_t* next_tcb =runqueue_remove(highest_prio);
	cur_tcb = next_tcb;

	// ctx switch to new task
	ctx_switch_half(&(next_tcb->context));
}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
	uint8_t highest_prio = highest_prio();

	tcb_t* temp_tcb = cur_tcb;
	// get task with highest prio in ready list
	tcb_t* next_tcb =runqueue_remove(highest_prio);
	cur_tcb = next_tcb;

	// ctx switch to new task
	ctx_switch_full(&(next_tcb->context), &(temp_tcb->context));
}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
	return cur_tcb -> cur_prio; 

/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)
{
	return (tcb_t *) cur_tcb; 
}