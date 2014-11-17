/**
 * @file mutex.c
 *
 * @brief Implements mutices.
 *
 * @author yangwu <yangwu@andrew.cmu.edu>
 *
 * 
 * @date  11.15.2014
 */

//#define DEBUG_MUTEX

#include <lock.h>
#include <task.h>
#include <sched.h>
#include <bits/errno.h>
#include <arm/psr.h>
#include <arm/exception.h>
#ifdef DEBUG_MUTEX
#include <exports.h> // temp
#endif

#define NULL (void *)0

mutex_t gtMutex[OS_NUM_MUTEX];
volatile int cur_mutex_num; // count number of mutex

void mutex_init() 
{
	cur_mutex_num = 0;
	int i;
	for(i=0; i<OS_NUM_MUTEX; i++)
	{
		gtMutex[i].bAvailable = 1;
		gtMutex[i].pHolding_Tcb = NULL;
		gtMutex[i].bLock = 0;
		gtMutex[i].pSleep_queue = NULL;
	}
}

int mutex_create(void)
{
	int i;

	disable_interrupts();

	if(cur_mutex_num == OS_NUM_MUTEX)
	{
		enable_interrupts();
		return -ENOMEM;
	}	

	for(i=OS_NUM_MUTEX-1; i>=0; i--)
	{
		if(gtMutex[i].bAvailable) // still availble mutex left
		{
			gtMutex[i].bAvailable = 0;
			return i;
		}
	}

	cur_mutex_num++;

	enable_interrupts();

	// after iteration, no available left
	return -ENOMEM;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
	if(mutex >= OS_NUM_MUTEX) 
		return EINVAL;

	mutex_t *cur_mutex = &(gtMutex[mutex]);
	tcb_t *cur_tcb = get_cur_tcb();
	// cannot acquire a holding mutex 
	if(cur_mutex->pHolding_Tcb==cur_tcb)
		return EDEADLOCK;

	disable_interrupts();

	// block
	if(cur_mutex->bLock)
	{
		tcb_t *s_queue;
		if(cur_mutex->pSleep_queue == NULL)
		{
			// put cur_tcb to sleep queue
			cur_mutex->pSleep_queue = cur_tcb;
			cur_tcb->sleep_queue = NULL;
		}
		else
		{
			s_queue = cur_mutex->pSleep_queue;
			while(s_queue->sleep_queue)
			{
				// move to next one in the list
				s_queue = s_queue->sleep_queue;
			}
			s_queue->sleep_queue = cur_tcb;
			cur_tcb->sleep_queue = NULL;
		}

		dispatch_sleep();
	}
	// unblock	
	else
	{
		cur_mutex->bLock = 1;
		//cur_mutex.bAvailable = 0;
		cur_mutex->pHolding_Tcb = get_cur_tcb();
		cur_tcb->cur_prio = 0;
		cur_tcb->holds_lock += 1;
	}

	enable_interrupts();

	return 0;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	mutex_t *cur_mutex = &(gtMutex[mutex]);
	tcb_t *next_tcb, *cur_tcb = get_cur_tcb();

	disable_interrupts();

	if(mutex>OS_NUM_MUTEX || mutex<0)
	{
		enable_interrupts();
		return -EINVAL;
	}

	if(cur_tcb!=cur_mutex->pHolding_Tcb)
	{
		enable_interrupts();
		return -EPERM;	
	}

	// release mutex
	cur_mutex->bLock = 0;
	cur_mutex->pHolding_Tcb = NULL;

	if(cur_mutex->pSleep_queue)
	{
		next_tcb = cur_mutex->pSleep_queue;
		cur_mutex->pSleep_queue = next_tcb->sleep_queue;
		next_tcb->sleep_queue = NULL;

		runqueue_add(next_tcb, next_tcb->cur_prio);
	}

	cur_tcb->holds_lock = cur_tcb->holds_lock - 1;

	if(cur_tcb->holds_lock == 0)
	{
		cur_tcb->cur_prio = cur_tcb->native_prio;
	}

	enable_interrupts();

	return 0;
}
