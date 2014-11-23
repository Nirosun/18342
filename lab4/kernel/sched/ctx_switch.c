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

//#ifdef DEBUG_MUTEX
#include <exports.h>
//#endif

static __attribute__((unused)) tcb_t* cur_tcb; /* use this if needed */

/**
 * @brief Initialize the current TCB and priority.
 *
 * Set the initialization thread's priority to IDLE so that anything
 * will preempt it when dispatching the first task.
 */
void dispatch_init(tcb_t* idle __attribute__((unused)))
{
	cur_tcb = idle;	

	// Idle should not in runnable queue
    runqueue_remove(cur_tcb->cur_prio);
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
	/*
	 * ToDo:
	 * #1 Put cur tcb to runnable queue
	 * #2 Update cur_tcb for getter
	 * #3 ctx switch
	 */
	 //if (cur_tcb->cur_prio > highest_prio())
	 //{
		// place cur tcb in queue, wait for next time slice
		tcb_t* temp_tcb = cur_tcb;
		runqueue_add(temp_tcb, temp_tcb->cur_prio);

		// get task with highest prio in ready list for getter
		uint8_t hi_prio = highest_prio();
		tcb_t* next_tcb =runqueue_remove(hi_prio);
		cur_tcb = next_tcb;

		// ctx switch with status save
		ctx_switch_full(&(next_tcb->context), &(temp_tcb->context));	 	
	 //}

}

/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * don't save the current task state.
 *
 * There is always an idle task to switch to.
 */
void dispatch_nosave(void)
{
#ifdef debug 
	printf("i'm dispatch_nosave..\n");
#endif

	//printf("Enter dispatch_nosave\n");

	uint8_t hi_prio = highest_prio();
	tcb_t* next_tcb =runqueue_remove(hi_prio);
	
	// ctx switch to new task
	cur_tcb = next_tcb;
	ctx_switch_half(&(next_tcb->context));

	//printf("Leave dispatch_nosave\n");
}


/**
 * @brief Context switch to the highest priority task that is not this task -- 
 * and save the current task but don't mark is runnable.
 *
 * There is always an idle task to switch to.
 */
void dispatch_sleep(void)
{
	//printf("Enter dispatch_sleep\n");
	tcb_t* temp_tcb = cur_tcb;

	uint8_t hi_prio = highest_prio();
	tcb_t* next_tcb =runqueue_remove(hi_prio);
	cur_tcb = next_tcb;

	// ctx switch with status save
	ctx_switch_full(&(next_tcb->context), &(temp_tcb->context));
}

/**
 * @brief Returns the priority value of the current task.
 */
uint8_t get_cur_prio(void)
{
	return cur_tcb -> cur_prio; 
}
/**
 * @brief Returns the TCB of the current task.
 */
tcb_t* get_cur_tcb(void)
{
	return cur_tcb; 
}
