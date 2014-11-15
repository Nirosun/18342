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

mutex_t gtMutex[OS_NUM_MUTEX];
volatile int cur_mutex_num;

void _disable_irq();
void _enable_irq();

void mutex_init() 
{
	cur_mutex_num = 0;
	int i;
	for(int i=0; i<OS_NUM_MUTEX; i++)
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

	_disable_irq();

	if(cur_mutex_num == OS_NUM_MUTEX)
	{
		_enable_irq();
		return -ENOMEN;
	}	

	for(int i=OS_NUM_MUTEX-1; i>=0; i--)
	{
		if(gtMutex[i].bAvailable) // still availble mutex left
		{
			gtMutex[i].bAvailable = 0;
			return i;
		}
	}

	cur_mutex_num++;

	_enable_irq();

	// after iteration, no available left
	return -ENOMEN;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
	if(mutex >= OS_NUM_MUTEX) 
		return EINVAL;

	mutex_t *cur_mutex = &(gtMutex[mutex]);
	tcb_t *cur_tcb = get_cur_tcb();
	// cannot acquire a holding mutex 
	if(cur_mutex.pHolding_Tcb==cur_tcb)
		return EDEADLOCK;

	_disable_irq();

	// block
	if(cur_mutex.bLock)
	{
		tcb_t *sleep_queue;
		if(cur_mutex->pSleep_queue == NULL)
		{
			// put cur_tcb to sleep queue
			cur_mutex->pSleep_queue = cur_tcb;
			cur_tcb->sleep_queue = NULL;
		}
		else
		{
			?????
		}

		dispatch_sleep();
	}
	// unblock	
	else
	{
		cur_mutex.bLock = 1;
		//cur_mutex.bAvailable = 0;
		cur_mutex.pHolding_Tcb = get_cur_tcb();
		cur_mutex.pHolding_Tcb->cur_prio = 0;
		cur_mutex.pHolding_Tcb->holds_lock = 1;
	}

	_enable_irq();

	return 1;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	return 1; // fix this to return the correct value
}

