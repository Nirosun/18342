/** @file time.c
 *
 * @brief Kernel timer based syscall implementations
 *
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date   2008-11-16
 */

#include <types.h>
#include <config.h>
#include <bits/errno.h>
#include <arm/timer.h>
#include <syscall.h>

extern volatile unsigned long os_time;

unsigned long time_syscall(void)
{
	/*
	 * return the volatile system time. unit:second
	 */ 
	//return os_time * ((unsigned long)10);
	return os_time;
}



/** @brief Waits in a tight loop for atleast the given number of milliseconds.
 *
 * @param millis  The number of milliseconds to sleep.
 *
 * 
 */
void sleep_syscall(unsigned long millis  __attribute__((unused)))
{	
 	//unsigned int finish_time = os_time + millis / OS_TIMER_RESOLUTION;
 	unsigned int finish_time = os_time + millis;
 	while (os_time < finish_time);
 		// do nothing, wait
 	return;
}
