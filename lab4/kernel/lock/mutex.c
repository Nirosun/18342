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

void _disable_irq();
void _enable_irq();

void mutex_init() 
{
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
	for(int i=OS_NUM_MUTEX-1; i>=0; i--)
	{
		if(gtMutex[i].bAvailable==1) // still availble mutex left
		{
			gtMutex[i].bAvailable = 0;
			return i;
		}
	}
	// after iteration, no available left
	return -ENOMEN;
}

int mutex_lock(int mutex  __attribute__((unused)))
{
	if(mutex >= OS_NUM_MUTEX) 
		return EINVAL;
	// cannot acquire a holding mutex 
	if(gtMutex[mutex].pHolding_Tcb==get_cur_tcb())
		return EDEADLOCK;

	_disable_irq();

	// block
	if(gtMutex[mutex].bLock==1 || gtMutex[mutex.bAvailable==0])
	{
		?????
	}
	// unblock	
	else
	{
		gtMutex[mutex].bLock = 1;
		gtMutex[mutex].bAvailable = 0;
		gtMutex[mutex].pHolding_Tcb = get_cur_tcb();
		gtMutex[mutex].pHolding_Tcb->cur_prio = 0;
		gtMutex[mutex].pHolding_Tcb->holds_lock = 1;
	}

	_enable_irq();

	return 1;
}

int mutex_unlock(int mutex  __attribute__((unused)))
{
	return 1; // fix this to return the correct value
}

