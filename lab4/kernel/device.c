/**
 * @file device.c
 *
 * @brief Implements simulated devices.
 * @author Kartik Subramanian <ksubrama@andrew.cmu.edu>
 * @date 2008-12-01
 */

#include <types.h>
#include <assert.h>

#include <task.h>
#include <sched.h>
#include <device.h>
#include <arm/reg.h>
#include <arm/psr.h>
#include <arm/exception.h>
#include <util.h>

/**
 * @brief Fake device maintainence structure.
 * Since our tasks are periodic, we can represent 
 * tasks with logical devices. 
 * These logical devices should be signalled periodically 
 * so that you can instantiate a new job every time period.
 * Devices are signaled by calling dev_update 
 * on every timer interrupt. In dev_update check if it is 
 * time to create a tasks new job. If so, make the task runnable.
 * There is a wait queue for every device which contains the tcbs of
 * all tasks waiting on the device event to occur.
 */

struct dev
{
	tcb_t* sleep_queue;
	tcb_t* sleep_tail;
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];

extern volatile unsigned long os_time;


/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
	int i;
	for(i=0; i<NUM_DEVICES; i++)
	{
		devices[i].sleep_queue = NULL;
		devices[i].sleep_tail  = NULL;
		devices[i].next_match  = os_time+dev_freq[i];
	} 
}


/**
 * @brief Puts a task to sleep on the sleep queue until the next
 * event is signalled for the device.
 *
 * @param dev  Device number.
 */
void dev_wait(unsigned int dev __attribute__((unused)))
{
	disable_interrupts();

	tcb_t *s_queue  = devices[dev].sleep_queue;
	tcb_t *tail_tcb = devices[dev].sleep_tail;
	tcb_t *cur_tcb  = get_cur_tcb();

	// no sleeping queue
	if(s_queue == NULL)
	{
		devices[dev].sleep_queue = cur_tcb;
		devices[dev].sleep_tail  = cur_tcb;
		devices[dev].sleep_queue->sleep_queue = NULL;
	}
	else
	{
		tail_tcb->sleep_queue = cur_tcb;
		tail_tcb = tail_tcb->sleep_queue;
		tail_tcb->sleep_queue = NULL;

		// update tail pointer
		devices[dev].sleep_tail = tail_tcb;
	}
	
	enable_interrupts();

	// make the task blocked
	dispatch_sleep();
}


/**
 * @brief Signals the occurrence of an event on all applicable devices. 
 * This function should be called on timer interrupts to determine that 
 * the interrupt corresponds to the event frequency of a device. If the 
 * interrupt corresponded to the interrupt frequency of a device, this 
 * function should ensure that the task is made ready to run 
 */
void dev_update(unsigned long millis __attribute__((unused)))
{
	tcb_t *first_tcb, *next_tcb;
	int i;

	// protect automonic
	disable_interrupts();

	for(i=0; i<NUM_DEVICES; i++)
	{
		if(millis > devices[i].next_match)
		{
			devices[i].next_match = millis + dev_freq[i];

            first_tcb = devices[i].sleep_queue;

            if (first_tcb == NULL) // no task waiting
            	goto end;
            else
            {	// wake up tasks
            	while (first_tcb != NULL)
	            {
	                next_tcb = first_tcb->sleep_queue;
	                first_tcb->sleep_queue = NULL; // out of sleep queue

	                runqueue_add(first_tcb, first_tcb->cur_prio);

	                first_tcb = next_tcb;
	            }
	            goto wake_up;
        	}	
		}
	}

wake_up:
    // active task from sleep queue
    dispatch_save();

end:
	enable_interrupts();
}
