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

#define NULL (void *)0

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
	unsigned long   next_match;
};
typedef struct dev dev_t;

/* devices will be periodically signaled at the following frequencies */
const unsigned long dev_freq[NUM_DEVICES] = {100, 200, 500, 50};
static dev_t devices[NUM_DEVICES];

extern volatile unsigned long os_time;

void _disable_irq();
void _enable_irq();

/**
 * @brief Initialize the sleep queues and match values for all devices.
 */
void dev_init(void)
{
	int i;
	for(i=0; i<NUM_DEVICES; i++)
	{
		devices[i].sleep_queue = NULL;
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
	_disable_irq();

	tcb_t *s_queue = devices[dev].sleep_queue;
	tcb_t *cur_tcb = get_cur_tcb();

	if(s_queue == NULL)
	{
		devices[dev].sleep_queue = cur_tcb;
		devices[dev].sleep_queue->sleep_queue = NULL;
	}
	else
	{
		while(s_queue->sleep_queue != NULL)
		{
			s_queue = s_queue->sleep_queue;
		}
		s_queue->sleep_queue = cur_tcb;
		s_queue = s_queue->sleep_queue;
		s_queue->sleep_queue = NULL;
	}
	
	_enable_irq();

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
	tcb_t *sleep_tcb, *next_tcb;
	int i, flag = 0;

	_disable_irq();

	for(i=0; i<NUM_DEVICES; i++)
	{
		if(devices[i].next_match < millis)
		{
			devices[i].next_match = millis + dev_freq[i];
            // Empty sleep queue
            sleep_tcb = devices[i].sleep_queue;
            devices[i].sleep_queue = NULL;

            // Put every tcb in sleep queue into run queue
            while (sleep_tcb != NULL)
            {
                flag = 1;
                runqueue_add(sleep_tcb, sleep_tcb->cur_prio);

                next_tcb = sleep_tcb->sleep_queue;
                sleep_tcb->sleep_queue = NULL;
                sleep_tcb = next_tcb;
            }
		}
	}

	_enable_irq();
}
